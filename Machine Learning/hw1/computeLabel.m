% This function computes the label for the given
% feature vector x using the linear separator represented by 
% the weight vector w and the threshold theta.
% YOU NEED TO WRITE THIS FUNCTION.

function y = computeLabel(x, w, theta)

PlaneResult=transpose(w)*x+theta;
if (PlaneResult>=0)
    y=1;
else
    y=-1;
end

end
