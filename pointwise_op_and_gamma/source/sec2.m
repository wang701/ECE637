% Section 2
close all;
clear all;

img = imread('kids.tif');
[EqImg Cdf] = equalize(img);
figure(1);
plot(Cdf);
xlabel('pixel intensity');
ylabel('$$\hat{F}_x(X_s)$$', 'Interpreter', 'Latex');
title('CDF for image kids.tif');
print('-dpng', '-r300', '../report/kids_cdf.png');
figure(2);
image(EqImg+1);
axis('image');
graymap = [0:255;0:255;0:255]'/255;
colormap(graymap);
print('-dpng', '-r300', '../report/kids_equ.png');
figure(3);
hist(EqImg(:),[0:255]);
xlabel('pixel intensity');
ylabel('number of pixels');
title('Histogram of equalized kids.tif');
print('-dpng', '-r300', '../report/kids_equ_hist.png');
