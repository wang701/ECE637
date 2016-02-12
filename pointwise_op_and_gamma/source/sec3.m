% Section 3
close all;
clear all;

img = imread('kids.tif');
strImg = stretch(img, 70, 180);
figure(1);
image(strImg+1);
axis('image');
graymap = [0:255;0:255;0:255]'/255;
colormap(graymap);
print('-dpng', '-r300', '../report/kids_str.png');
figure(2);
hist(strImg(:),[0:255]);
xlabel('pixel intensity');
ylabel('number of pixels');
title('Histogram of stretched kids.tif');
print('-dpng', '-r300', '../report/kids_str_hist.png');
