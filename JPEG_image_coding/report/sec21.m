% Section 2.1 %

clear all;
close all;

img = imread('img03y.tif');
gamma = [0.25 1 4];

for i = 1:3
	writeDq(sprintf('img03y_%d.dq', i), img, gamma(i));
	imgRes = readDq(sprintf('img03y_%d.dq', i), gamma(i));
	imgDiff = 10 * (img - imgRes) + 128;

	figure;
	image(img);
	truesize;
	colormap(gray(256));

	figure;
	image(imgRes);
	truesize;
	colormap(gray(256));
	imwrite(uint8(imgRes), sprintf('img03y_%d.tif', i));

	figure;
	image(imgDiff);
	truesize;
	colormap(gray(256));
	imwrite(uint8(imgDiff), sprintf('img03y_diff_%d.tif', i));
end
