function DrawPaperFigure_Initial(General,Cohesion,Result,Control,Beam)

Case=General.Case;
NoPullUp=General.NoPullUp;
DeltaBar=General.DeltaBar;
DeltaC=Cohesion.DeltaC;

NumberOfPT=Beam.NOP;

Value=Result.x;
Ener_Bending=Result.Ener_Bend;
Equilibrium=Result.CheckEquili;
EquiPortionAve=Result.AveEquili;
Traction=Result.Traction;
Seperation=Result.Seperation;

ValueBR=Result.xBR;
Ener_BendingBR=Result.Ener_BendBR;
TractionBR=Result.TractionBR;

NoEta=Control.NoData.Eta;
NoBeta=Control.NoData.Beta;
BetaRecord=Control.BetaRecord;
EtaRecord=Control.EtaRecord;

xint = linspace(0,1,NumberOfPT);
%% This Draws the geometry and setting
% xint_3=linspace(0.5,2.5,3*NumberOfPT);
% 
% figure(100)
% Plot_ShapeSubs=plot(xint_3,cos(2*pi.*xint_3));
% hold on;
% 
% set(Plot_ShapeSubs,'LineWidth',5,'Color',[0 0 0]);
% 
% axis off;

%% This Draws a bended beam with different negative cohesive force color
% PickData=[27];
% Substrate=cos(2*pi.*xint);
% 
% ValueTemp=reshape(Value(1,PickData(1,1),1,:),1,NumberOfPT);
% Above=ValueTemp(ValueTemp+1>Substrate)+1;
% AboveX=xint(ValueTemp+1>Substrate);
% Below=ValueTemp(~(ValueTemp+1>Substrate))+1;
% BelowX=xint(~(ValueTemp+1>Substrate));
% 
% figure(1000)
% Plot_ShapeSubs=plot(xint,cos(2*pi.*xint));
% hold on;
% Plot_Above=plot(AboveX,Above);
% hold on;
% Plot_Below=plot(xint,ValueTemp+1);
% hold on;
% 
% axis off;
% 
% set(Plot_ShapeSubs,'LineWidth',5,'Color',[0 0 0]);
% set(Plot_Above,'LineWidth',3,'Color',[1 0 0],'LineStyle','-');
% set(Plot_Below,'LineWidth',3,'Color',[1 0 0],'LineStyle','--');
%% For Figure 1 and 2 ,eta=5,beta=3*10^-6~2*10^-4, 80 data is good
%%%% Figure 1 is the bending energy ratio of the initial profile
% PickData=[7;26;27;40;];
% BetaRecord_mainline=[0;BetaRecord];
% Ener_Bending_mainline=[0;reshape(Ener_Bending(1,:,1),NoBeta,1)];
% figure(1)
% Point_Beta=BetaRecord(PickData(:,1),1);
% Point_Bend=Ener_Bending(1,PickData(:,1),1);
% Str_Points=['A';'B';'C';'D';];
% 
% Plot_MainLine=plot(BetaRecord_mainline,Ener_Bending_mainline);
% hold on;
% Plot_Points=plot(Point_Beta,Point_Bend);
% hold off
% Plot_text=text(Point_Beta-0.08*10^-4,Point_Bend+0.02,Str_Points);
% 
% set(Plot_MainLine,'LineWidth',3,'Color',[0 0 1]);
% set(Plot_Points,'LineStyle','none','Marker','o','MarkerSize',9,'MarkerEdgeColor','none','MarkerFaceColor',[1 0 0]);
% Plot_xlabel=xlabel('$$\beta$$','Interpreter','latex');
% Plot_ylabel=ylabel('$$\widetilde{E}_{b}$$','interpreter','latex');
% Plot_legend=legend('Bending Energy Ratio \eta=5');
% axis([0 BetaRecord(NoBeta,1) 0 0.6]);
% 
% set(Plot_legend,'FontName','Helvetica','FontSize',16);
% set(gca, ...
%     'FontName','Helvetica',...
%     'FontSize',16,...
%     'Box', 'off','TickDir','out',...
%     'YGrid','on','XMinorTick','on','YMinorTick','on',...
%     'XTick',0:0.5*10^-4:2*10^-4,'YTick',0:0.1:0.6);
% set(Plot_text,'FontName','Helvetica',...
%     'FontSize',18,...
%     'FontWeight','Bold');
% set(Plot_xlabel,'FontWeight','bold','FontSize',23);
% set(Plot_ylabel,'FontWeight','bold','FontSize',23);
%% For Figure 1 and 2 ,eta=5,beta=3*10^-6~2*10^-4, 80 data is good
%%%%% figure 2 is the initial profile of the selected points in figure 1
%%%%% the two PidckData need to be the same
% figure(2)
% PickData=[7;26;27;40;];
% Str_Points2=['A';'B';'C';'D';];
% Str_Posi2=[0.65 -0.9;0.5 -0.7;0.5 0.2;0.5 0.7];
% 
% Plot_ShapeSubs=plot(xint,cos(2*pi.*xint));
% hold on;
% Temp=reshape(Value(1,PickData(1,1),1,:),1,NumberOfPT);
% Plot_ShapeBeam1=plot(xint,(Temp+1));
% hold on;
% Temp=reshape(Value(1,PickData(2,1),1,:),1,NumberOfPT);
% Plot_ShapeBeam2=plot(xint,(Temp+1));
% hold on;
% Temp=reshape(Value(1,PickData(3,1),1,:),1,NumberOfPT);
% Plot_ShapeBeam3=plot(xint,(Temp+1));
% hold on;
% Temp=reshape(Value(1,PickData(4,1),1,:),1,NumberOfPT);
% Plot_ShapeBeam4=plot(xint,(Temp+1));
% hold on;
% Plot_text2=text(Str_Posi2(:,1),Str_Posi2(:,2),Str_Points2);
% hold off;
% 
% axis([0 1 -1 1.5]);
% Plot_xlabel=xlabel('$$\frac{x}{L}$$','Interpreter','latex','FontSize',16);
% Plot_ylabel=ylabel('$$\frac{w}{A}$$','Interpreter','latex','FontSize',16);
% Plot_legend2=legend('The substrate profile','The gold film deformed profile');
% 
% set(Plot_ShapeSubs,'LineWidth',5,'Color',[0 0 0]);
% set(Plot_ShapeBeam1,'LineWidth',3,'Color',[1 0 0],'LineStyle','--');
% set(Plot_ShapeBeam2,'LineWidth',3,'Color',[1 0 0],'LineStyle','--');
% set(Plot_ShapeBeam3,'LineWidth',3,'Color',[1 0 0],'LineStyle','--');
% set(Plot_ShapeBeam4,'LineWidth',3,'Color',[1 0 0],'LineStyle','--');
% set(Plot_text2,'FontName','Helvetica',...
%     'FontSize',18,...
%     'FontWeight','Bold');
% set(gca, ...
%     'FontName','Helvetica',...
%     'FontSize',16,...
%     'Box', 'off','TickDir','out',...
%     'YGrid','on','XMinorTick','on','YMinorTick','on',...
%     'XTick',0:0.2:1,'YTick',-1:0.5:1.5);
% set(Plot_legend2,'FontName','Helvetica','FontSize',16);
% set(Plot_xlabel,'FontWeight','bold','FontSize',23);
% set(Plot_ylabel,'FontWeight','bold','FontSize',23);

%% This part plot the curves one by one or some by some in an trial and error sense with different beta number, also need to change the string. Note there is no hold off
%%%% This part draws the bending energy of different eta
%%%% From 3*10^-6~5*10^-4: Eta=2.5 20pt; eta=3 40pt; eta=4 100pt smooth;eta=5
%%%% 80pt; eta=7 80pt; eta=9 80pt
% figure(3)
% for i=1:NoEta
%     BetaRecord_mainline=[0;BetaRecord];
%     Ener_Bending_mainline=[0;reshape(Ener_Bending(i,:,1),NoBeta,1)];
%     Str_Eta='\eta=9';
%     [MaxY,MaxX]=max(Ener_Bending_mainline);
%     
%     Plot_MainLine=plot(BetaRecord_mainline,Ener_Bending_mainline);
%     hold on;
%     Plot_text=text(BetaRecord_mainline(MaxX,1)+0.1e-4,MaxY+0.02,Str_Eta);
%     hold on;
%     
%     Plot_xlabel=xlabel('$$\beta$$','Interpreter','latex');
%     Plot_ylabel=ylabel('$$\widetilde{E}_{b}$$','interpreter','latex');
%     Plot_legend=legend('Bending Energy Ratio');
%     axis([0 BetaRecord(NoBeta,1) 0 0.6]);
%     
%     set(Plot_MainLine,'LineWidth',2,'Color',[0 0 1]);
%     set(Plot_text,'FontName','Helvetica',...
%         'FontSize',16,...
%         'FontWeight','Bold');
%     set(gca, ...
%         'FontSize',16,...
%         'FontName','Helvetica',...
%         'Box', 'off','TickDir','out',...
%         'YGrid','on','XMinorTick','on','YMinorTick','on',...
%         'XTick',0:0.5*10^-4:BetaRecord(NoBeta,1),'YTick',0:0.1:0.6);
%     set(Plot_xlabel,'FontWeight','bold','FontSize',23);
%     set(Plot_ylabel,'FontWeight','bold','FontSize',23);
%     set(Plot_legend,'FontName','Helvetica','FontSize',16);
% end

%% This is to draw a 3D figure of the effective bending energy
load EtaSet.mat EtaSet;
load BetaSet.mat BetaSet;


load EtaSet.mat EtaSet;
load BetaSet.mat BetaSet;

EtaNew=reshape(EtaSet,size(EtaSet,1)*size(EtaSet,2),1);
BetaNew=reshape(EtaSet,size(BetaSet,1)*size(BetaSet,2),1);

PickEta=55;
% for m=1:NoBeta;
% PickBeta=m;
EtaRerod_mainline=[0;EtaRecord];
BetaRecord_mainline=[0;BetaRecord];
Ener_Bend_3D=zeros(NoEta+1,NoBeta+1);
Ener_Bend_3D(2:end,2:end)=reshape(Ener_Bending(:,:,1),NoEta,NoBeta);

figure(4)

% Point_Eta=EtaRecord(PickEta+1);
% Point_Beta=BetaRecord(PickBeta+1);
% Point_Ener=Ener_Bend_3D(PickBeta+1,PickEta+1);
Point_Eta=EtaNew
Point_Beta=BetaNew
Point_Ener=repmat(0.6,size(EtaSet,1)*size(EtaSet,2),1);

surf(BetaRecord_mainline,EtaRerod_mainline,Ener_Bend_3D);
hold on;
colorbar('ZTickLabel',...
    {'Freezing','Cold','Cool','Neutral',...
     'Warm','Hot','Burning','Nuclear'})
% Plot_Points=plot3(Point_Beta,Point_Eta,Point_Ener);
% hold off;
% Plot_text=text(Point_Beta-0.08*10^-4,Point_Eta-0.2,Point_Bend+0.02,Str_Points);

    Plot_xlabel=xlabel('$$\beta$$','Interpreter','latex');
    Plot_ylabel=ylabel('$$\eta$$','Interpreter','latex');
%     Plot_zlabel=zlabel('$$\widetilde{E}_{b}$$','interpreter','latex');
    axis([0 BetaRecord(end,1) 0 EtaRecord(end,1) 0 0.8]);
% set(Plot_Points,'LineStyle','none','Marker','o','MarkerSize',8,'MarkerEdgeColor','none','MarkerFaceColor',[1 0 0]);

    set(gca, ...
        'FontSize',30,...
        'FontName','Helvetica',...
        'Box', 'off','TickDir','out',...
        'XMinorTick','on','YMinorTick','on');
    set(Plot_xlabel,'FontWeight','bold','FontSize',35);
    set(Plot_ylabel,'FontWeight','bold','FontSize',35);
%     set(Plot_zlabel,'FontWeight','bold','FontSize',23);



% Plot_MainLine=plot(BetaRecord_mainline,Ener_Bending_mainline);
% hold on;
% Plot_Points=plot(Point_Beta,Point_Bend);
% hold off
% Plot_text=text(Point_Beta-0.08*10^-4,Point_Bend+0.02,Str_Points);
% 
% set(Plot_MainLine,'LineWidth',3,'Color',[0 0 1]);
% Plot_xlabel=xlabel('$$\beta$$','Interpreter','latex');
% Plot_ylabel=ylabel('$$\widetilde{E}_{b}$$','interpreter','latex');
% Plot_legend=legend('Bending Energy Ratio \eta=5');
% axis([0 BetaRecord(NoBeta,1) 0 0.6]);

% set(Plot_legend,'FontName','Helvetica','FontSize',16);
% set(gca, ...
%     'FontName','Helvetica',...
%     'FontSize',16,...
%     'Box', 'off','TickDir','out',...
%     'YGrid','on','XMinorTick','on','YMinorTick','on',...
%     'XTick',0:0.5*10^-4:2*10^-4,'YTick',0:0.1:0.6);
% set(Plot_text,'FontName','Helvetica',...
%     'FontSize',18,...
%     'FontWeight','Bold');
% set(Plot_xlabel,'FontWeight','bold','FontSize',23);
% set(Plot_ylabel,'FontWeight','bold','FontSize',23);