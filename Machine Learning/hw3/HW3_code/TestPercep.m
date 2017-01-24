function [mist]=TestPercep(labels,data,w,theta)

% keep the number of example and the dimension of data
data_size=size(data,1);
data_dimension=size(data,2);

% Initialize the mistakes
mist=0;

for i=1:data_size
    Pred=sign(transpose(w)*transpose(data(i,:))+theta);
    if Pred~=labels(i,1)
        mist=mist+1;
    end
end

disp('Best case in Percep has error : ');disp(mist);