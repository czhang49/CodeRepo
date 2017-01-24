%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Problem 1 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [BestCase,mistakes]=Problem1(ParamSet)


l=ParamSet(1,1);
m=ParamSet(1,2);
n=ParamSet(1,3);
noise=ParamSet(1,4);

Times_Tune=ParamSet(1,5);
Times_Train=ParamSet(1,6);
number=ParamSet(1,7);
data_tunesize=ParamSet(1,8);
Interval_train=ParamSet(1,9);        % This value better be 50, 100 , 200 ... similar good values 

%% Get the data and label and set the tuning parameters
%Generate the data, row is size of data, col is the dimension of data
[labels_pool,data_pool]=gen(l,m,n,number,noise);
[labels_d1,data_d1,labels_d2,data_d2]=GetPercentData(labels_pool,data_pool,data_tunesize);
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

%% Regenarate d1 and d2, use the best parameter to train against.
[vec_trainsize]=GetTrainSize(data_size,Interval_train);
num_train=size(vec_trainsize,1);

mistakes=zeros(5,num_train);

for i=1:num_train
    if mod(i,10)==1
        disp('The number of training with best case is');disp(i);
    end
    [labels_pool,data_pool]=gen(l,m,n,number,noise);
    [labels_d1,data_d1]=GetPercentDataOnlyD1(labels_pool,data_pool,vec_trainsize(i,1));

    [~,~,mistakes(1,i)]=TrainPercep(labels_d1,data_d1,Times_Train);
    [~,~,mistakes(2,i)]=TrainPercepWithMar(labels_d1,data_d1,Times_Train,B_percepwithmar_eta);
    [~,~,mistakes(3,i)]=TrainWinnow(labels_d1,data_d1,Times_Train,B_winnow_alpha);
    [~,~,mistakes(4,i)]=TrainWinnowWithMar(labels_d1,data_d1,Times_Train,B_winnowwithmar_alpha,B_winnowwithmar_gamma);
    [~,~,mistakes(5,i)]=TrainAdaGrad(labels_d1,data_d1,Times_Train,B_adagrad_eta);
end

mistakes=reshape(mistakes,1,5,num_train);
