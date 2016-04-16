% Section 3.1 %

clear all;
close all;

img = imread('house.tif');
[m, n] = size(img);

graymap = [0:255;0:255;0:255]'/255;
colormap(graymap);
img_thres = (img > 127) * 255;
image(img_thres);
truesize
imwrite(img_thres, '../report/house_t_127.tif');

img_d = double(img);
img_thres_d = double(img_thres);

rmse = sqrt((1 / (n * m)) * sum(sum((img_d - img_thres_d).^2)));

fid = fidelity(img, img_thres);
