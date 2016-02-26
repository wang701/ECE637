% Section 4.1: Eigenimages, PCA, and Data Reduction

close all;
clear all;

read_data; % this creates vector X
mu_hat = mean(X,2);
[r,c] = size(X);
Z = zeros(r,c);
Z = (1/sqrt(n-1))*(bsxfun(@minus,X,mu_hat));
[U S V] = svd(Z,0);

for k=1:12
  img=reshape(U(:,k),64,64);
  figure(1); subplot(4,3,k); imagesc(img);
  axis('image'); colormap(gray(256));
  title(strcat('eigenvalue',num2str(k)),'Interpreter','none');
end
print('-dpng', '-r300', '../report/12eigimgs.png');

Y = U'*(bsxfun(@minus,X,mu_hat));
figure(2);
for k = 1:4
	plot(1:10,Y(1:10,k));
	hold on;
end
legend('a','b','c','d');
xlabel('Eigenvector number');
ylabel('Projection value');
print('-dpng', '-r300', '../report/projCoefVseigNum.png');

img = reshape(X(:,1),64,64);
figure(3);
imagesc(img);
axis('image'); colormap(gray(256));
print('-dpng', '-r300', '../report/orgA.png');

m = 1;
for k = [1 5 10 15 20 30]
	Xtmp = U(:,1:k)*Y(1:k,:);
	Xest = bsxfun(@plus,Xtmp,mu_hat);
	img = reshape(Xest(:,1),64,64);
	figure(4); subplot(3,2,m); image(img);
	title(strcat('"a" from ',num2str(k),' eigenvectors'));
	axis('image'); colormap(gray(256));
	m = m+1;
end
print('-dpng', '-r300', '../report/synA.png');
