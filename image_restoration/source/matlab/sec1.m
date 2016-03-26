% Section 1 %

clear all;
clc;
close all;

%{
	restoring from blurred image
%}

X = imread('../../images/img14bl.tif');
X = double(X);

Y = imread('../../images/img14g.tif');
Y = double(Y);

[r, c] = size(Y);
M = floor(r / 20);
N = floor(c / 20);
B = M * N;
Z = zeros(B, 49);
Y_col = zeros(B , 1);

i = 1;
for j = 1:M
   for k = 1:N
       Z(i,:) = reshape(X(20*j - 3:20*j + 3, 20*k - 3:20*k + 3)', [1, 49]);
       Y_col(i) = Y(20 * j, 20 * k);
       i = i + 1;
    end
end

R_zz = (Z' * Z) ./ B;
r_zy = (Z' * Y_col) ./ B;
theta_star = R_zz \ r_zy;
theta = reshape(theta_star, [7, 7]);
theta
imgout = conv2(X, theta);
figure(1);
image(uint8(imgout));
axis('image');
colormap([0:255;0:255;0:255]'/255);
print('-dpng', '-r300', '../../report/nobl.png');


%{
	restoring from noisy image
%}

clear all;
close all;

X = imread('../../images/img14gn.tif');
X = double(X);

Y = imread('../../images/img14g.tif');
Y = double(Y);

[r, c] = size(Y);
M = floor(r / 20);
N = floor(c / 20);
B = M * N;
Z = zeros(B, 49);
Y_col = zeros(B , 1);

i = 1;
for j = 1:M
   for k = 1:N
       Z(i,:) = reshape(X(20*j - 3:20*j + 3, 20*k - 3:20*k + 3)', [1, 49]);
       Y_col(i) = Y(20 * j, 20 * k);
       i = i + 1;
    end
end

R_zz = (Z' * Z) ./ B;
r_zy = (Z' * Y_col) ./ B;
theta_star = R_zz \ r_zy;
theta = reshape(theta_star, [7, 7]);
theta
imgout = conv2(X, theta);
figure(1);
image(uint8(imgout));
axis('image');
colormap([0:255;0:255;0:255]'/255);
print('-dpng', '-r300', '../../report/non.png');

%{
	restoring from spotty image
%}

clear all;
close all;

X = imread('../../images/img14sp.tif');
X = double(X);

Y = imread('../../images/img14g.tif');
Y = double(Y);

[r, c] = size(Y);
M = floor(r / 20);
N = floor(c / 20);
B = M * N;
Z = zeros(B, 49);
Y_col = zeros(B , 1);

i = 1;
for j = 1:M
   for k = 1:N
       Z(i,:) = reshape(X(20*j - 3:20*j + 3, 20*k - 3:20*k + 3)', [1, 49]);
       Y_col(i) = Y(20 * j, 20 * k);
       i = i + 1;
    end
end

R_zz = (Z' * Z) ./ B;
r_zy = (Z' * Y_col) ./ B;
theta_star = R_zz \ r_zy;
theta = reshape(theta_star, [7, 7]);
theta
imgout = conv2(X, theta);
figure(1);
image(uint8(imgout));
axis('image');
colormap([0:255;0:255;0:255]'/255);
print('-dpng', '-r300', '../../report/nosp.png');

%{

theta =

    0.3720   -0.0431   -0.3541    1.1089    0.3791   -1.0990    1.1560
    0.2052    0.4069   -0.3242   -2.4308   -0.4590   -0.1802    0.4776
   -0.9682   -1.2219   -0.4810    1.9317   -1.1045   -0.2944   -1.7439
    1.0572   -0.0280    0.3321    3.7782    1.2263    1.0624    0.6483
    0.1961   -0.6146    0.7580    1.5691    0.8358   -1.8928    0.2949
   -1.0020   -1.3229   -0.0871   -0.0701   -1.4710   -1.9628    0.2604
    0.9254    0.4024   -0.7923    0.0615    0.3905    0.8127    0.3042


theta =

    0.0165   -0.0055   -0.0105   -0.0091   -0.0050   -0.0044   -0.0053
    0.0259    0.0053   -0.0125   -0.0153   -0.0222    0.0079   -0.0043
    0.0044    0.0355    0.0674    0.0476    0.0423    0.0307    0.0154
    0.0050    0.0205    0.0731    0.2306    0.1117    0.0268    0.0127
   -0.0080    0.0464    0.0470    0.0891    0.0650    0.0088    0.0140
    0.0302    0.0091    0.0290   -0.0175   -0.0118   -0.0063    0.0183
   -0.0259    0.0066   -0.0030    0.0011    0.0069    0.0192    0.0054


theta =

    0.0080    0.0017   -0.0010   -0.0014    0.0252   -0.0099   -0.0407
    0.0048   -0.0016    0.0042   -0.0203    0.0023   -0.0006    0.0162
   -0.0016    0.0558    0.0413    0.0350    0.0612    0.0313   -0.0068
   -0.0050    0.0267    0.0968    0.2652    0.0965    0.0497    0.0100
    0.0257    0.0435    0.0212    0.1492    0.0154    0.0143    0.0079
   -0.0209    0.0214   -0.0196   -0.0287   -0.0412    0.0038    0.0129
   -0.0185    0.0196    0.0199    0.0083    0.0233    0.0131   -0.0110

%}
