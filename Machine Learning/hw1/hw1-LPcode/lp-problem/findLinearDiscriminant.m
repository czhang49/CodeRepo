% This function finds a linear discriminant using LP
% The linear discriminant is represented by 
% the weight vector w and the threshold theta.
% YOU NEED TO FINISH IMPLEMENTATION OF THIS FUNCTION.

function [w,theta,delta] = findLinearDiscriminant(data)
%% setup linear program
[m, np1] = size(data);
n = np1-1;
% write your code here
A=zeros(m,n+2);
for i=1:m
    A(i,1:(end-2))=data(i,end)*data(i,1:end-1);     % Each row in A is Y(i)*the original row
    A(i,end-1)=data(i,end);                         % the second last digit is Y(i)
    A(i,end)=1;                                     % the last digit is 1
end
c=[zeros(n+1,1);1];
b=ones(m,1);

Lowerbound=[ones(n+1,1)*(-inf);0];
%% solve the linear program
%adjust for matlab input: A*x <= b
[t, z] = linprog(c, -A, -b,[],[],Lowerbound);

%% obtain w,theta,delta from t vector
w = t(1:n);
theta = t(n+1);
delta = t(n+2);

end
