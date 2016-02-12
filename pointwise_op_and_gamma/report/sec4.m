%Section 4
linearImg = imread('linear.tif');
corLinearImg = 255*(double(linearImg)/255).^(double(1/2.583));
figure(1);
image(uint8(corLinearImg)+1);
axis('image');
graymap = [0:255;0:255;0:255]'/255;
colormap(graymap);
print('-dpng', '-r300', '../report/linear_gamma.png');

gammaImg = imread('gamma15.tif');
corGammaImg = 255*(double(gammaImg)/255).^(double(1.5/2.583));
figure(2);
image(uint8(corGammaImg)+1);
axis('image');
colormap(graymap);
print('-dpng', '-r300', '../report/gamma15_gamma.png');
