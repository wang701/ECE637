%% Section 1 %%

% Clear memory and close existing figures
clear
close all

[img] = imread('img04g.tif');

map = gray(256);
fig4 = figure(4);
colormap(fig4, map);
image(uint8(img));
axis('image');
imwrite(uint8(img), '../report/gs_img_4g.png');

X = double(img)/255;

% Select an NxN region of the image and store it in the variable "z"

p=100;
q=100;

N = 64;
z = X(p:(N+p-1), q:(N+q-1));

% Compute the power spectrum for the NxN region
Z = (1/N^2)*abs(fft2(z)).^2;

% Use fftshift to move the zero frequencies to the center of the plot
Z = fftshift(Z);

% Compute the logarithm of the Power Spectrum.
Zabs = log(Z);

% Plot the result using a 3-D mesh plot and label the x and y axises properly. 
x = 2*pi*((0:(N-1)) - N/2)/N;
y = 2*pi*((0:(N-1)) - N/2)/N;
fig1 = figure(1); 
mesh(x,y,Zabs);
xlabel('\mu');
ylabel('\nu');
print('-dpng','-r300','../report/psd_64x64.png');

% N = 128 %
N = 128;
z = X(p:(N+p-1), q:(N+q-1));
Z = (1/N^2)*abs(fft2(z)).^2;
Z = fftshift(Z);
Zabs = log(Z);
x = 2*pi*((0:(N-1)) - N/2)/N;
y = 2*pi*((0:(N-1)) - N/2)/N;
fig2 = figure(2); 
mesh(x,y,Zabs);
xlabel('\mu');
ylabel('\nu');
print('-dpng','-r300','../report/psd_128x128.png');

% N = 256 %
N = 256;
z = X(p:(N+p-1), q:(N+q-1));
Z = (1/N^2)*abs(fft2(z)).^2;
Z = fftshift(Z);
Zabs = log(Z);
x = 2*pi*((0:(N-1)) - N/2)/N;
y = 2*pi*((0:(N-1)) - N/2)/N;
fig3 = figure(3); 
mesh(x,y,Zabs);
xlabel('\mu');
ylabel('\nu');
print('-dpng','-r300','../report/psd_256x256.png');

% Use BetterSpecAnal.m %
[Z_better, fig5] = BetterSpecAnal(img);
print('-dpng','-r300','../report/psd_better.png');

%% Section 2 %%

img_rand = -0.5 + (0.5+0.5)*rand(512);
img_rand_s = 255 * (img_rand+0.5);
fig6 = figure(6);
colormap(fig6, map);
image(uint8(img_rand_s));
axis('image');
imwrite(uint8(img_rand_s), '../report/randimg.png');

img_f = zeros(512, 512);
for m = 1:512
	for n = 1:512
		img_f(m,n) = 3 * img_rand(m,n);
		if (m > 1)
			img_f(m,n) = img_f(m,n) + 0.99*img_f(m-1,n);
		end
		if (n > 1)
			img_f(m,n) = img_f(m,n) + 0.99*img_f(m,n-1);
		end
		if (m > 1 && n > 1)
			img_f(m,n) = img_f(m,n) - 0.9801*img_f(m-1,n-1);
		end
	end
end

fig7 = figure(7);
colormap(fig7, map);
image(uint8(img_f+127));
axis('image');
imwrite(uint8(img_f+127), '../report/randimg_f.png');

% Theoretical PSD %
u = -pi:0.1:pi;
v = -pi:0.1:pi;
[U,V] = meshgrid(u,v);
sigma = 1/12;
S_y = abs(3./((1-0.99*exp(-1i*U)).*(1-0.99*exp(-1i*V)))).^2*sigma;
fig8 = figure(8);
mesh(U,V,log(S_y));
xlabel('\mu');
ylabel('\nu');
print('-dpng','-r300','../report/psd_theo.png');

% Estimated PSD %
[est_S_y, fig9] = BetterSpecAnal(img_f);
print('-dpng','-r300','../report/psd_esti.png');




