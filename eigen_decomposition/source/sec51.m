% Section 5.1: Classification and PCA

close all;
clear all;

read_data; % this creates vector X
mu_hat = mean(X,2);
Z = (1/sqrt(n-1))*(bsxfun(@minus,X,mu_hat));
[U S V] = svd(Z,0);
A = U(:,1:10);
Y = A'*((bsxfun(@minus,X,mu_hat)));

Ck=10;
empty_cell = cell(26,2);
params = cell2struct(empty_cell,{'M','R'},2);

for k = 1:1:26
	mu_k_hat = mean(Y,2);
	params(k).M = mu_k_hat;
	Z_k = bsxfun(@minus,Y,mu_k_hat);
	params(k).R = Z_k*Z_k'/(312-1);
end

read_test_data;
TY = A'*((bsxfun(@minus,TX,mu_hat)));

for k = 1:1:26
	y_minus_mu_k = bsxfun(@minus,TY,A'*params(k).M);
	R_k = A'*params(k).R*A;
	[k_min k_star] = min(y_minus_mu_k'*inv(R_k)*y_minus_mu_k + log(abs(R_k)));
end
