% This function solves the LP problem for a given weight vector
% to find the threshold theta.
% YOU NEED TO FINISH IMPLEMENTATION OF THIS FUNCTION.

function [theta,delta] = findLinearThreshold(data,w)
%% setup linear program
[m, np1] = size(data);
n = np1-1;

% write your code here
A=zeros(m,2);
for i=1:m
    A(i,1)=data(i,end);                         % the second last digit is Y(i)
    A(i,end)=1;                                     % the last digit is 1
end
clear i;
b=zeros(m,1);
for i=1:m
    b(i,1)=1-transpose(w)*transpose(data(i,1:end-1))*data(i,end);
end
clear i;

c=[0;1];
Lowerbound=[-inf;0];
%% solve the linear program
%adjust for matlab input: A*x <= b
[t, z] = linprog(c, -A, -b,[],[],Lowerbound);

%% obtain w,theta,delta from t vector
% w = t(1:n);
% theta = t(n+1);
% delta = t(n+2);
theta = t(1);
delta = t(2);
end
