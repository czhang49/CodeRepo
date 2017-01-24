function [w,theta,mist]=TrainPercepForW(labels,data,R)

% keep the number of example and the dimension of data
data_size=size(data,1);
data_dimension=size(data,2);

% initilization of w and theta and number of mistakes
eta=1;
w=zeros(data_dimension,1);
theta=0;
mist=0;
counter_nomistake=0;
counter_cycle=0;

% Do the training and keep record of the mistakes
while counter_nomistake<R
    for i=1:data_size
        predict=sign(transpose(w)*transpose(data(i,:))+theta);
        if predict~=labels(i,1)
            counter_nomistake=0;
            mist=mist+1;
            w=w+transpose(data(i,:)*labels(i,1)*eta);
            theta=theta+labels(i,1)*eta;
        else
            counter_nomistake=counter_nomistake+1;
        end
        if counter_nomistake>=R
            break;
        end
    end
    disp('Find continuous no mistake Perceptron cycle through entire pool number: ');disp(counter_cycle+1);
end