function [w,theta,mist]=TrainWinnowWithMar(labels,data,TrainTimes,alpha,gamma)


% keep the number of example and the dimension of data
data_size=size(data,1);
data_dimension=size(data,2);
alpha_size=length(alpha);
gamma_size=length(gamma);

% initilization of w and theta and number of mistakes, note alpha is the
% row and gamma is the column
w=ones(alpha_size,gamma_size,data_dimension);
theta=ones(alpha_size,gamma_size)*(-data_dimension);
mist=zeros(alpha_size,gamma_size);

for p=1:alpha_size
    for q=1:gamma_size
        for m=1:TrainTimes
            for i=1:data_size
                predict=sign(reshape(w(p,q,:),1,data_dimension)*transpose(data(i,:))+theta(p,q,1));
                value=reshape(w(p,q,:),1,data_dimension)*transpose(data(i,:))+theta(p,q,1);
                if predict~=labels(i,1)
                    mist(p,q,1)=mist(p,q,1)+1;
                end
                if value*labels(i,1)<=gamma(q,1)
                    for j=1:data_dimension
                        w(p,q,j)=w(p,q,j)*alpha(p,1)^(labels(i,1)*data(i,j));
                    end
                end
            end
        end
    end
end