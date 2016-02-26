% Section 2.2: Covariance Estimation and Whitening

close all;
clear all;

axis('equal');

Rx = [2 -1.2;-1.2 1];
W = randn(2,1000);
[E,Lamda] = eig(Rx);
X_tilda = ((Lamda)^(1/2))*W;
X = E*X_tilda;

mu_hat = (1/1000)*sum(X);
Z = zeros(2,1000);
Z(1,:) = X(1,:) - mu_hat;
Z(2,:) = X(2,:) - mu_hat;
R_hat = (1/999)*(Z*Z');

[E,Lamda] = eig(R_hat);
X_tilda_esti = E'*X;
W_esti = ((Lamda)^(-1/2))*E'*X;
figure(1);
plot(X_tilda_esti(1,:),X_tilda_esti(2,:),'.');
xlabel('$\tilde{X_1}$','Interpreter','LaTex');
ylabel('$\tilde{X_2}$','Interpreter','LaTex');
print('-dpng', '-r300', '../report/rvXtildaEsti.png');
figure(2);
plot(W_esti(1,:),W_esti(2,:),'.');
xlabel('W_1');
ylabel('W_2');
print('-dpng', '-r300', '../report/rvWEsti.png');
