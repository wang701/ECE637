% Section 4 %

close all;
clear all;

% Step 1 %
data = load('data.mat');
reflect = load('reflect.mat');
lambda = 400:10:700;
R = reflect.R;
x = data.x;
y = data.y;
z = data.z;
illum1 = data.illum1;
illum2 = data.illum2;

% Step 2 %
I = bsxfun(@times, R, permute(illum1, [3 1 2]));

% Step 3 %
[m, n, ~] = size(I);
XYZ = zeros(m,n,3);

for p = 1:m
	for q = 1:n
		XYZ(p,q,:) = permute(I(p,q,:), [1 3 2]) * [x;y;z]';
	end
end

% Step 4 %
x_wp = 0.3127; y_wp = 0.3290; z_wp = 0.3583;
RGB_709 = [0.64 0.33 0.03;0.3 0.6 0.1;0.15 0.06 0.79];
%D65_wp = [x_wp y_wp z_wp];
k_rgb = inv(RGB_709) * [x_wp/y_wp 1 z_wp/y_wp]';
M = RGB_709 * diag(k_rgb);

% Step 5 %
rgb = zeros(m,n,3);

for p = 1:m
	for q = 1:n
		rgb(p,q,:) = permute(XYZ(p,q,:), [1 3 2]) * inv(M);
	end
end

% Step 6 %
rgb(rgb(:) > 1) = 1;
rgb(rgb(:) < 0) = 0;

figure(1);
image(rgb);

% Step 7 %
gc_rgb = zeros(m,n,3);

gc_rgb = 255 * (rgb / 255).^(2.2);
%{
for p = 1:m
	for q = 1:n
		for r = 1:3
			%gc_rgb(p,q,r) = 255 * (double(rgb(p,q,r)) / 255).^(double(2.2));
			gc_rgb(p,q,r) = 255 * (rgb(p,q,r) / 255).^(2.2);
		end
	end
end
%}

figure(2);
image(gc_rgb);
