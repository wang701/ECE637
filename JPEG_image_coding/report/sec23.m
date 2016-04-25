% Section 2.3 %

clear all;
close all;

img = imread('img03y.tif');
gamma = 1;

imgRes = readDq('img03y_3.dq', gamma);
