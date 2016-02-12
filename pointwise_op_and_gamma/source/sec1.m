% Section 1
close all;
clear all;

[raceimg] = imread('race.tif');
figure(1);
image(raceimg+1);
axis('image');
graymap = [0:255;0:255;0:255]'/255;
colormap(graymap);

[kidimg] = imread('kids.tif');
figure(2);
image(kidimg+1);
axis('image');
colormap(graymap);

figure(3);
hist(raceimg(:),[0:255]);
xlabel('pixel intensity');
ylabel('number of pixels');
title('Histogram of race.tif');
print('-dpng', '-r300', '../report/race_hist.png');
figure(4);
hist(kidimg(:),[0:255]);
xlabel('pixel intensity');
ylabel('number of pixels');
title('Histogram of kids.tif');
print('-dpng', '-r300', '../report/kids_hist.png');
