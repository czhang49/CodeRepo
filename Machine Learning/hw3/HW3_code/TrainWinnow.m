function [w,theta,mist]=TrainWinnow(labels,data,TrainTimes,alpha)

% keep the number of example and the dimension of data
data_size=size(data,1);
data_dimension=size(data,2);
alpha_size=length(alpha);

% initilization of w and theta and number of mistakes
w=ones(alpha_size,data_dimension);
theta=ones(alpha_size,1)*(-data_dimension);
mist=zeros(alpha_size,1);

for p=1:alpha_size
    for m=1:TrainTimes
        for i=1:data_size
            predict=sign(reshape(w(p,:),1,data_dimension)*transpose(data(i,:))+theta(p,1));
            if predict~=labels(i,1)
                mist(p,1)=mist(p,1)+1;
                for j=1:data_dimension
                    w(p,j)=w(p,j)*alpha(p,1)^(labels(i,1)*data(i,j));
                end
            end
        end
    end
end