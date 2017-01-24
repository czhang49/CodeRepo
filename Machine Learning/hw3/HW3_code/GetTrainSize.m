function [vec_trainsize]=GetTrainSize(data_size,Interval_train)

vec_trainsize=0:Interval_train:data_size;
vec_trainsize(1,1)=1;

vec_trainsize=transpose(vec_trainsize);
