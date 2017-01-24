function [w,theta,mist]=TrainAdaGradForW(labels,data,R,eta)

% keep the number of example and the dimension of data
data_size=size(data,1);
data_dimension=size(data,2);
eta_size=length(eta);

% initilization of w and theta and number of mistakes
gamma=1;
w=zeros(eta_size,data_dimension);
theta=zeros(eta_size,1);
mist=zeros(eta_size,1);
G_w=zeros(eta_size,data_dimension);
G_theta=zeros(eta_size,1);
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
                G_theta(p,1)=G_theta(p,1)+(-labels(i,1))^2;
                theta(p,1)=theta(p,1)+labels(i,1)*eta(p,1)/sqrt(G_theta(p,1));
                for j=1:data_dimension
                    G_w(p,j)=G_w(p,j)+(-labels(i,1)*data(i,j))^2;
                    if G_w(p,j)~=0
                        w(p,j)=w(p,j)+data(i,j)*labels(i,1)*eta(p,1)/sqrt(G_w(p,j));
                    end
                end
            end
            if counter_nomistake>=R
                break;
            end
        end
        disp('Find continuous no mistake AdaGrad cycle through entire pool number: ');disp(counter_cycle+1);
    end
end