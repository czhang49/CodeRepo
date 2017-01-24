%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Problem 1 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [BestCase,mistakes]=Problem3(ParamSet)
%ParamSet: l m n tuneTimes trainTimes DataNoise TuneSize DataClean
l=ParamSet(1,1);
m=ParamSet(1,2);
n=ParamSet(1,3);

Times_Tune=ParamSet(1,4);
Times_Train=ParamSet(1,5);
number=ParamSet(1,6);
data_tunesize=ParamSet(1,7);
data_size_clean=ParamSet(1,8);

%% Get the data and label and set the tuning parameters
%Generate the data, row is size of data, col is the dimension of data
[labels_pool,data_pool]=gen(l,m,n,number,1);
[labels_d1,data_d1,~,~]=GetPercentData(labels_pool,data_pool,data_tunesize);
data_size=size(data_pool,1);
data_dimension=size(data_pool,2);

percepwithmar_eta=[1.5;0.25;0.03;0.005;0.001;];
winnow_alpha=[1.1;1.01;1.005;1.0005;1.0001];
winnowwithmar_alpha=[1.1;1.01;1.005;1.0005;1.0001];
winnowwithmar_gamma=[2;0.3;0.04;0.006;0.001];
adagrad_eta=[1.5;0.25;0.03;0.005;0.001];

%% do the training for each algorithm

[w_percep,theta_percep,train_percep]=TrainPercep(labels_d1,data_d1,Times_Tune);
[w_percepwithmar,theta_percepwithmar,train_percepwithmar]=TrainPercepWithMar(labels_d1,data_d1,Times_Tune,percepwithmar_eta);
[w_winnow,theta_winnow,train_winnow]=TrainWinnow(labels_d1,data_d1,Times_Tune,winnow_alpha);
[w_winnowwithmar,theta_winnowwithmar,train_winnowwithmar]=TrainWinnowWithMar(labels_d1,data_d1,Times_Tune,winnowwithmar_alpha,winnowwithmar_gamma);
[w_adagrad,theta_adagrad,train_adagrad]=TrainAdaGrad(labels_d1,data_d1,Times_Tune,adagrad_eta);

%% do the testing for each algorithm
[labels_d2,data_d2]=gen(l,m,n,data_size_clean,0);

[test_percep]=TestPercep(labels_d2,data_d2,w_percep,theta_percep);
[test_percepwithmar]=TestPercepWithMar(labels_d2,data_d2,w_percepwithmar,theta_percepwithmar);
[test_winnow]=TestWinnow(labels_d2,data_d2,w_winnow,theta_winnow);
[test_winnowwithmar]=TestWinnowWithMar(labels_d2,data_d2,w_winnowwithmar,theta_winnowwithmar);
[test_adagrad]=TestAdaGrad(labels_d2,data_d2,w_adagrad,theta_adagrad);

%% Select the best cases
[B_percepwithmar_eta,B_winnow_alpha,B_winnowwithmar_alpha,B_winnowwithmar_gamma,B_adagrad_eta]=...
SortOutBest(test_percepwithmar,percepwithmar_eta,test_winnow,winnow_alpha,test_winnowwithmar,...
winnowwithmar_alpha,winnowwithmar_gamma,test_adagrad,adagrad_eta);

BestCase=[B_percepwithmar_eta,B_winnow_alpha,B_winnowwithmar_alpha,B_winnowwithmar_gamma,B_adagrad_eta];

%% This to use the best case to train again and then do the testing 
mistakes=zeros(1,5);

[w_percep,theta_percep,train_percep]=TrainPercep(labels_pool,data_pool,Times_Train);
[w_percepwithmar,theta_percepwithmar,train_percepwithmar]=TrainPercepWithMar(labels_pool,data_pool,Times_Train,B_percepwithmar_eta);
[w_winnow,theta_winnow,train_winnow]=TrainWinnow(labels_pool,data_pool,Times_Train,B_winnow_alpha);
[w_winnowwithmar,theta_winnowwithmar,train_winnowwithmar]=TrainWinnowWithMar(labels_pool,data_pool,Times_Train,B_winnowwithmar_alpha,B_winnowwithmar_gamma);
[w_adagrad,theta_adagrad,train_adagrad]=TrainAdaGrad(labels_pool,data_pool,Times_Train,B_adagrad_eta);

[test_percep]=TestPercep(labels_d2,data_d2,w_percep,theta_percep);
[test_percepwithmar]=TestPercepWithMar(labels_d2,data_d2,w_percepwithmar,theta_percepwithmar);
[test_winnow]=TestWinnow(labels_d2,data_d2,w_winnow,theta_winnow);
[test_winnowwithmar]=TestWinnowWithMar(labels_d2,data_d2,w_winnowwithmar,theta_winnowwithmar);
[test_adagrad]=TestAdaGrad(labels_d2,data_d2,w_adagrad,theta_adagrad);

mistakes=[test_percep test_percepwithmar test_winnow test_winnowwithmar test_adagrad];
mistakes=mistakes/data_size_clean;