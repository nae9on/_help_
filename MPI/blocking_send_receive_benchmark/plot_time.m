clc
clear all
close all

ulimit = 2e-3;

% intra socket communication
data10 = csvread('./intraSocket_1TPP/log.1.0',2,0); %s0,c0
data11 = csvread('./intraSocket_1TPP/log.1.1',2,0); %s0,c1
data20 = csvread('./intraSocket_9TPP/log.1.0',2,0); %s0,c0-c8
data21 = csvread('./intraSocket_9TPP/log.1.1',2,0); %s0,c9-c17
figure(1);
%(column2 send, column3 recv)
plot(data10(:,1),data10(:,2),'b'); hold on %send
plot(data11(:,1),data11(:,2),'-.b'); hold on %recv
plot(data11(:,1),data11(:,3),'-.r'); hold on %send
plot(data10(:,1),data10(:,3),'r'); hold on %recv

plot(data20(:,1),data20(:,2),'g'); hold on %send
plot(data21(:,1),data21(:,2),'-.g'); hold on %recv
plot(data21(:,1),data21(:,3),'-.k'); hold on %send
plot(data20(:,1),data20(:,3),'k'); hold on %recv
legend('send-0-1TPP','receive-1-1TPP','send-1-1TPP','receive-0-1TPP',...
       'send-0-9TPP','receive-1-9TPP','send-1-9TPP','receive-0-9TPP');
title('intra socket comm');
ylim([0 ulimit]);

% intra node communication
data30 = csvread('./intraNode_1TPP/log.1.0',2,0); %s0,c0
data31 = csvread('./intraNode_1TPP/log.1.1',2,0); %s1,c0
figure(2);
plot(data30(:,1),data30(:,2),'b'); hold on %send
plot(data31(:,1),data31(:,2),'-.b'); hold on %recv
plot(data31(:,1),data31(:,3),'-.r'); hold on %send
plot(data30(:,1),data30(:,3),'r'); hold on %recv
legend('send-0','receive-1','send-1','receive-0');
title('intra node comm');
ylim([0 ulimit]);

% inter node communication
data40 = csvread('./interNode_1TPP/log.1.0',2,0); % n0, not bound
data41 = csvread('./interNode_1TPP/log.1.1',2,0); % n1, not bound
data50 = csvread('./interNode_1TPP_Binding/log.1.0',2,0); % n0, s0, c0
data51 = csvread('./interNode_1TPP_Binding/log.1.1',2,0); % n0, s0, c0
figure(3);
plot(data40(:,1),data40(:,2),'b'); hold on %send
plot(data41(:,1),data41(:,2),'-.b'); hold on %recv
plot(data41(:,1),data41(:,3),'-.r'); hold on %send
plot(data40(:,1),data40(:,3),'r'); hold on %recv
plot(data50(:,1),data50(:,2),'g'); hold on %send
plot(data51(:,1),data51(:,2),'-.g'); hold on %recv
plot(data51(:,1),data51(:,3),'-.k'); hold on %send
plot(data50(:,1),data50(:,3),'k'); hold on %recv
legend('send-0-unbound','receive-1-unbound','send-1-unbound','receive-0-unbound',...
       'send-0-bound','receive-1-bound','send-1-bound','receive-0-bound');
title('inter node comm');
ylim([0 ulimit]);