% Section 5.1 %

clear all;
close all;

fg = imread('house.tif');
fo = errDiffusion(fg);
[m, n] = size(fg);

graymap = [0:255;0:255;0:255]'/255;
colormap(graymap);
image(fo);
truesize
imwrite(fo, '../report/house_ed.tif');

rmse = sqrt((1 / (n * m)) * sum(sum((double(fg) - fo).^2)));
fid = fidelity(double(fg), fo);
