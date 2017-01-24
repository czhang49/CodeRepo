function [w,theta,mist]=TrainPercepWithMarForW(labels,data,R,eta)


% keep the number of example and the dimension of data
data_size=size(data,1);
data_dimension=size(data,2);
eta_size=length(eta);

% initilization of w and theta and number of mistakes
gamma=1;
w=zeros(eta_size,data_dimension);
theta=zeros(eta_size,1);
mist=zeros(eta_size,1);
counter_nomistake=0;
counter_cycle=0;

for p=1:eta_size
    while counter_nomistake<R
        for i=1:data_size
            predict=sign(reshape(w(p,:),1,data_dimension)*transpose(data(i,:))+theta(p,1));
            value=reshape(w(p,:),1,data_dimension)*transpose(data(i,:))+theta(p,1);
            if predict~=labels(i,1)
                mist(p,1)=mist(p,1)+1;
                counter_nomistake=0;
            else 
                counter_nomistake=counter_nomistake+1;
            end
            if value*labels(i,1)<=gamma
                w(p,:)=w(p,:)+data(i,:)*labels(i,1)*eta(p,1);
                theta(p,1)=theta(p,1)+labels(i,1)*eta(p,1);
            end
            if counter_nomistake>=R
                break;
            end
        end    
        disp('Find continuous no mistake Perceptron With Margin cycle through entire pool number: ');disp(counter_cycle+1);
    end
end