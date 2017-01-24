function [labels_d1,data_d1]=GetPercentDataOnlyD1(labels_pool,data_pool,data_size)

data_pool_size=size(data_pool,1);

rows_d1=linspace(1,data_size,data_size);

labels_d1=labels_pool(rows_d1,:);
data_d1=data_pool(rows_d1,:);