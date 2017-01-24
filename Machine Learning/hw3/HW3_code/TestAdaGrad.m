function [mist]=TestAdaGrad(labels,data,w,theta)

% keep the number of example and the dimension of data
data_size=size(data,1);
data_dimension=size(data,2);
w_size=size(w,1);

% Initialize the mistakes
mist=zeros(w_size,1);

for p=1:w_size
    for i=1:data_size
        Pred=sign(w(p,:)*transpose(data(i,:))+theta(p,1));
        if Pred~=labels(i,1)
            mist(p,1)=mist(p,1)+1;
        end
    end
end