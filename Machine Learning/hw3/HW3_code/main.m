%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%% HW 3 CS 446 Fall 2014 Main Chen Zhang %%%%%%%%%%%%%%%%%

%% To do problem 1
% %ParamSet: l m n noise tuneTimes trainTimes DataPool TuneSize IntervalTrain
% ParamSetP1=[10 100 500 0 20 1 50000 5000 100;
%             10 100 1000 0 20 1 50000 5000 100;];
% num_ParamSetP1=size(ParamSetP1,1);
% 
% % here the datasize and train interval for different paramSet need be same
% [vec_trainsize1]=GetTrainSize(ParamSetP1(1,7),ParamSetP1(1,9));
% num_train1=size(vec_trainsize1,1);
% 
% BestCaseP1=zeros(num_ParamSetP1,5);     % This 5 is 5 parameters in total
% MistakesP1=zeros(num_ParamSetP1,5,num_train1);  % This 5 is 5 algorithms
% 
% % Do the calculation for different parameter sets
% for i=1:num_ParamSetP1
%     [BestCaseP1(i,:),MistakesP1(i,:,:)]=Problem1(ParamSetP1(i,:));
% end
% 
% save BestCaseP1.mat BestCaseP1;
% save MistakesP1.mat MistakesP1;
% save vec_trainsize1.mat vec_trainsize1;

%% To do problem 2
% R=1000;
% %ParamSet: l m n noise tuneTimes trainTimes DataPool TuneSize IntervalTrain
% ParamSetP2=[10 20 40 0 20 1 50000 5000 50;
%             10 20 80 0 20 1 50000 5000 50;
%             10 20 120 0 20 1 50000 5000 50;
%             10 20 160 0 20 1 50000 5000 50;
%             10 20 200 0 20 1 50000 5000 50;];
% num_ParamSetP2=size(ParamSetP2,1);
% 
% BestCaseP2=zeros(num_ParamSetP2,5);      % This 5 is 5 parameters in total
% MistakesP2=zeros(num_ParamSetP2,5);      % This 5 is 5 algorithms
% 
% % Do the calculation for different parameter sets
% for i=1:num_ParamSetP2
%     [BestCaseP2(i,:),MistakesP2(i,:)]=Problem2(ParamSetP2(i,:),R);
% end
% 
% save BestCaseP2.mat BestCaseP2;
% save MistakesP2.mat MistakesP2;
    
%% To do problem 3
%ParamSet: l m n tuneTimes trainTimes DataNoise TuneSize DataClean
%From the requirement we know that the tune and train times need to be 20
% ParamSetP3=[10 100 1000  20 20 50000 5000 10000;
%             10 500 1000  20 20 50000 5000 10000;
%             10 1000 1000  20 20 50000 5000 10000;];
% num_ParamSetP3=size(ParamSetP3,1);
% 
% BestCaseP3=zeros(num_ParamSetP3,5);     % This 5 is 5 parameters in total
% MistakesP3=zeros(num_ParamSetP3,5);     % This 5 is 5 algorithms, percent
% 
% % Do the calculation for different parameter sets
% for i=1:num_ParamSetP3
%     [BestCaseP3(i,:),MistakesP3(i,:)]=Problem3(ParamSetP3(i,:));
% end
% 
% save BestCaseP3.mat BestCaseP3;
% save MistakesP3.mat MistakesP3;

%% To do bonus problem
ParamSetBonus=[10,100,1000,20;
                10,500,1000,20;
                10,1000,1000,20;];
num_ParamSet=size(ParamSetBonus,1);

mistakes=zeros(2,3);
for i=1:num_ParamSet
    l=ParamSetBonus(i,1);
    m=ParamSetBonus(i,2);
    n=ParamSetBonus(i,3);
    Train_times=ParamSetBonus(i,4);
    [train_y,train_x]=unba_gen(l,m,n,50000,0.1);
    [test_y,test_x]=unba_gen(l,m,n,10000,0.1);
    
    [w_percep,theta_percep,~]=TrainPercep(train_y,train_x,Train_times);
    [w_percepwithmar,theta_percepwithmar,~]=TrainPercepWithMar(train_y,train_x,Train_times,0.03);

    [test_percep]=TestPercep(test_y,test_x,w_percep,theta_percep);
    [test_percepwithmar]=TestPercepWithMar(test_y,test_x,w_percepwithmar,theta_percepwithmar);

    mistakes(1,i)=test_percep;
    mistakes(2,i)=test_percepwithmar;
    
end
mistakes=mistakes/10000;
       
%% To do the plotting
% This part is to load all the necessary data
% load BestCaseP1.mat BestCaseP1;
% load MistakesP1.mat MistakesP1;
% load vec_trainsize1.mat vec_trainsize1;
%
% load BestCaseP2.mat BestCaseP2;
% load MistakesP2.mat MistakesP2;
%
% load BestCaseP3.mat BestCaseP3;
% load MistakesP3.mat MistakesP3;

% This par to draw figure of problem 1
% for i=1:size(MistakesP1,1)
%     figure(i)
%     str='Perceptron';
%     plot_mist_percep=plot(vec_trainsize1, reshape(MistakesP1(i,1,:),size(vec_trainsize1,1),1));
%     hold on;
%     plot_mist_percepwithmar=plot(vec_trainsize1, reshape(MistakesP1(i,2,:),size(vec_trainsize1,1),1));
%     hold on;
%     plot_mist_winnow=plot(vec_trainsize1, reshape(MistakesP1(i,3,:),size(vec_trainsize1,1),1));
%     hold on;
%     plot_mist_winnowwithmar=plot(vec_trainsize1, reshape(MistakesP1(i,4,:),size(vec_trainsize1,1),1));
%     hold on;
%     plot_mist_adagrad=plot(vec_trainsize1, reshape(MistakesP1(i,5,:),size(vec_trainsize1,1),1));
%     hold on;
%     plot_text=text(2500,300,str);
%     plot_text2=text(2500,300,str);  % Need to put the text to position and change coorespondingly
%     plot_text3=text(2500,300,str);
%     plot_text4=text(2500,300,str);
%     plot_text5=text(2500,300,str);
%     plot_text6=text(2500,300,str);  % This largest text serve as the title of the graph
%     hold off
%     
%     plot_xlabel=xlabel('Number Of Examples');
%     plot_ylabel=ylabel('Number Of Mistakes');
%     
%     set(plot_mist_percep,'LineWidth',2,'Color',[0 0 1]);
%     set(plot_mist_percepwithmar,'LineWidth',2,'Color',[0 1 0]);
%     set(plot_mist_winnow,'LineWidth',2,'Color',[1 0 0]);
%     set(plot_mist_winnowwithmar,'LineWidth',2,'Color',[0 0 0]);
%     set(plot_mist_adagrad,'LineWidth',2,'Color',[0.5 0.5 0.5]);
%     plot_legend=legend('plot_mist_percep','plot_mist_percepwithmar','plot_mist_winnow','plot_mist_winnowwithmar','plot_mist_adagrad');
%     
%     set(plot_text,'FontName','Helvetica',...
%         'FontSize',20,...
%         'FontWeight','Bold');
%     set(plot_text2,'FontName','Helvetica',...
%         'FontSize',20,...
%         'FontWeight','Bold');
%     set(plot_text3,'FontName','Helvetica',...
%         'FontSize',20,...
%         'FontWeight','Bold');
%     set(plot_text4,'FontName','Helvetica',...
%         'FontSize',20,...
%         'FontWeight','Bold');
%     set(plot_text5,'FontName','Helvetica',...
%         'FontSize',20,...
%         'FontWeight','Bold');
%     set(plot_text6,'FontName','Helvetica',...
%         'FontSize',30,...
%         'FontWeight','Bold');
%     set(gca, ...
%         'FontSize',35,...
%         'FontName','Helvetica',...
%         'Box', 'off','TickDir','out',...
%         'YGrid','on','XMinorTick','on','YMinorTick','on');
%     set(plot_xlabel,'FontWeight','bold','FontSize',25);
%     set(plot_ylabel,'FontWeight','bold','FontSize',25);
%     set(plot_legend,'FontName','Helvetica','FontSize',16);
%     
% end

% This part do the drawing for problem 2
% N=[40 80 120 160 200];
% figure(3)
% str='Perceptron';
% plot_mist_percep=plot(N,MistakesP2(:,1));
% hold on;
% plot_mist_percepwithmar=plot(N,MistakesP2(:,2));
% hold on;
% plot_mist_winnow=plot(N,MistakesP2(:,3));
% hold on;
% plot_mist_winnowwithmar=plot(N,MistakesP2(:,4));
% hold on;
% plot_mist_adagrad=plot(N,MistakesP2(:,5));
% hold on;
% plot_text=text(0,0,str);
% plot_text2=text(0,0,str);  % Need to put the text to position and change coorespondingly
% plot_text3=text(0,0,str);
% plot_text4=text(0,0,str);
% plot_text5=text(0,0,str);
% plot_text6=text(0,0,str);  % This largest text serve as the title of the graph
% hold off
% 
% plot_xlabel=xlabel('n');
% plot_ylabel=ylabel('Number Of Mistakes');
% 
% set(plot_mist_percep,'LineWidth',2,'Color',[0 0 1]);
% set(plot_mist_percepwithmar,'LineWidth',2,'Color',[0 1 0]);
% set(plot_mist_winnow,'LineWidth',2,'Color',[1 0 0]);
% set(plot_mist_winnowwithmar,'LineWidth',2,'Color',[0 0 0]);
% set(plot_mist_adagrad,'LineWidth',2,'Color',[0.5 0.5 0.5]);     % This legend is to be deleted.
% plot_legend=legend('plot_mist_percep','plot_mist_percepwithmar','plot_mist_winnow','plot_mist_winnowwithmar','plot_mist_adagrad');
% 
% set(plot_text,'FontName','Helvetica',...
%     'FontSize',20,...
%     'FontWeight','Bold');
% set(plot_text2,'FontName','Helvetica',...
%     'FontSize',20,...
%     'FontWeight','Bold');
% set(plot_text3,'FontName','Helvetica',...
%     'FontSize',20,...
%     'FontWeight','Bold');
% set(plot_text4,'FontName','Helvetica',...
%     'FontSize',20,...
%     'FontWeight','Bold');
% set(plot_text5,'FontName','Helvetica',...
%     'FontSize',20,...
%     'FontWeight','Bold');
% set(plot_text6,'FontName','Helvetica',...
%     'FontSize',30,...
%     'FontWeight','Bold');
% set(gca, ...
%     'FontSize',35,...
%     'FontName','Helvetica',...
%     'Box', 'off','TickDir','out',...
%     'YGrid','on','XMinorTick','on','YMinorTick','on');
% set(plot_xlabel,'FontWeight','bold','FontSize',25);
% set(plot_ylabel,'FontWeight','bold','FontSize',25);
% set(plot_legend,'FontName','Helvetica','FontSize',16);