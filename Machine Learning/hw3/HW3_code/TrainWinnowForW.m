function [w,theta,mist]=TrainWinnowForW(labels,data,R,alpha)

% keep the number of example and the dimension of data
data_size=size(data,1);
data_dimension=size(data,2);
alpha_size=length(alpha);

% initilization of w and theta and number of mistakes
w=ones(alpha_size,data_dimension);
theta=ones(alpha_size,1)*(-data_dimension);
mist=zeros(alpha_size,1);
counter_nomistake=0;
counter_cycle=0;

for p=1:alpha_size
    while counter_nomistake<R
        for i=1:data_size
            predict=sign(reshape(w(p,:),1,data_dimension)*transpose(data(i,:))+theta(p,1));
            if predict~=labels(i,1)
                mist(p,1)=mist(p,1)+1;
                counter_nomistake=0;
                for j=1:data_dimension
                    w(p,j)=w(p,j)*alpha(p,1)^(labels(i,1)*data(i,j));
                end
            else 
                counter_nomistake=counter_nomistake+1;
            end
            if counter_nomistake>=R
                break;
            end
        end
        disp('Find continuous no mistake Winnow Basic cycle through entire pool number: ');disp(counter_cycle+1);
    end
end