function [w,theta,mist]=TrainPercep(labels,data,TrainTimes)

% keep the number of example and the dimension of data
data_size=size(data,1);
data_dimension=size(data,2);

% initilization of w and theta and number of mistakes
eta=1;
w=zeros(data_dimension,1);
theta=0;
mist=0;

% Do the training and keep record of the mistakes
for m=1:TrainTimes
    for i=1:data_size
        predict=sign(transpose(w)*transpose(data(i,:))+theta);
        if predict~=labels(i,1)
            mist=mist+1;
            w=w+transpose(data(i,:)*labels(i,1)*eta);
            theta=theta+labels(i,1)*eta;
        end
    end
end
