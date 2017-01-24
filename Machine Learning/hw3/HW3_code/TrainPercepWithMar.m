function [w,theta,mist]=TrainPercepWithMar(labels,data,TrainTimes,eta)


% keep the number of example and the dimension of data
data_size=size(data,1);
data_dimension=size(data,2);
eta_size=length(eta);

% initilization of w and theta and number of mistakes
gamma=1;
w=zeros(eta_size,data_dimension);
theta=zeros(eta_size,1);
mist=zeros(eta_size,1);

for p=1:eta_size
    for m=1:TrainTimes
        for i=1:data_size
            predict=sign(reshape(w(p,:),1,data_dimension)*transpose(data(i,:))+theta(p,1));
            value=reshape(w(p,:),1,data_dimension)*transpose(data(i,:))+theta(p,1);
            if predict~=labels(i,1)
                mist(p,1)=mist(p,1)+1;
            end
            if value*labels(i,1)<=gamma
                w(p,:)=w(p,:)+data(i,:)*labels(i,1)*eta(p,1);
                theta(p,1)=theta(p,1)+labels(i,1)*eta(p,1);
            end
        end
    end
end