% Section 5 %

close all;
clear all;

[x, y] = meshgrid(0:0.005:1);
z = 1 - y - x;

RGB_709 = [0.64 0.3 0.15;0.33 0.6 0.06;0.03 0.1 0.79];
M_709 = RGB_709 * eye(3);

[m, n] = size(x);
XYZ = zeros(m,n,3);

XYZ(:,:,1) = x;
XYZ(:,:,2) = y;
XYZ(:,:,3) = z;

rgb = zeros(m,n,3);

for p = 1:m
	for q = 1:n
		rgb(p,q,:) = M_709 \ permute(XYZ(p,q,:), [1 3 2])';
	end
end

rgb(rgb(:) < 0) = 1;

gc_rgb = zeros(m,n,3);
gc_rgb = ((rgb).^(1/2.2));


figure(1);
image([0:0.005:1], [0:0.005:1], gc_rgb);
axis('xy');
hold on;

data = load('data.mat');
lambda = 400:10:700;
x0 = data.x;
y0 = data.y;
z0 = data.z;

x1 = x0(:) ./ (x0(:) + y0(:) + z0(:));
y1 = y0(:) ./ (x0(:) + y0(:) + z0(:));
plot(x1, y1, 'r-');
