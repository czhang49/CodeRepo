% This function plots the linear discriminant.
% YOU NEED TO IMPLEMENT THIS FUNCTION

function plot2dSeparator(w, theta)

if length(w)~=2
    error('The length of the line coefficients is not two');
end

X1=-1;
X2=1;
Y1=(-w(1)*X1-theta)/w(2);
Y2=(-w(1)*X2-theta)/w(2);

figure(1)
plot([X1 X2],[Y1 Y2]);
% txt='\delta';
% text(1,1,txt);

% axis([-2 2 -2 2]);

end
