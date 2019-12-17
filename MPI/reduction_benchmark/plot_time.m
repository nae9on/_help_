clc
clear all

NN = 16; % Number of Nodes
Xaxis = [];
data2 = [];
for itr=1:NN
    if NN<10
        log = strcat('log.1.',num2str(itr-1));
    else
        log = strcat('log.1.',num2str(floor((itr-1)/10)),num2str(mod(itr-1,10)));
    end
    fprintf("file = %s\n",log);
    temp = csvread(strcat('./interNode_Reduce_',num2str(NN),'Node/',log),2,0);
    Xaxis = temp(:,1);
    data2 = [data2 temp(:,2)];
end
figure(1);
hold on
plot(Xaxis,data2(:,end));