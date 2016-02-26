% Section 2.1: Generating Gaussian Random Vectors

close all;
clear all;

axis('equal');

Rx = [2 -1.2;-1.2 1];
W = randn(2,1000);
figure(1);
plot(W(1,:),W(2,:),'.');
xlabel('W_1');
ylabel('W_2');
print('-dpng', '-r300', '../report/rvW.png');

[E,Lamda] = eig(Rx);
X_tilda = ((Lamda)^(1/2))*W;
figure(2);
plot(X_tilda(1,:),X_tilda(2,:),'.');
xlabel('$\tilde{X_1}$','Interpreter','LaTex');
ylabel('$\tilde{X_2}$','Interpreter','LaTex');
print('-dpng', '-r300', '../report/rvXtilda.png');

X = E*X_tilda;
figure(3);
plot(X(1,:),X(2,:),'.');
xlabel('X_1');
ylabel('X_2');
print('-dpng', '-r300', '../report/rvX.png');
