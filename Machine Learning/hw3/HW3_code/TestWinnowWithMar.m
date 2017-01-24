function [mist]=TestWinnowWithMar(labels,data,w,theta)

% keep the number of example and the dimension of data
data_size=size(data,1);
data_dimension=size(data,2);
w_size_1=size(w,1);
w_size_2=size(w,2);

% Initialize the mistakes
mist=zeros(w_size_1,w_size_2);

for p=1:w_size_1
    for q=1:w_size_2
        for i=1:data_size
            Pred=sign(reshape(w(p,q,:),1,data_dimension)*transpose(data(i,:))+theta(p,q));
            if Pred~=labels(i,1)
                mist(p,q)=mist(p,q)+1;
            end
        end
    end
end