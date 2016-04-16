% Section 4.2 %

clear all;
close all;

I2 = [1 2;3 0];
I4 = [4*I2 + 1, 4*I2 + 2; 4*I2 + 3, 4*I2];
I8 = [4*I4 + 1, 4*I4 + 2; 4*I4 + 3, 4*I4];

fg = imread('house.tif');
fl = 255 * (double(fg) / 255).^(2.2);
[m, n] = size(fg);

N2 = 2;
N4 = 4;
N8 = 8;

T2 = 255 * ((I2 + 0.5) / (N2^2));
T4 = 255 * ((I4 + 0.5) / (N4^2));
T8 = 255 * ((I8 + 0.5) / (N8^2));

fl_2 = zeros(m,n);
fl_4 = zeros(m,n);
fl_8 = zeros(m,n);

for p = 1:m
	for q = 1:n
		r = mod(p-1,N2) + 1;
		s = mod(q-1,N2) + 1;
		if fl(p,q) > T2(r,s)
			fl_2(p,q) = 255;
		else
			fl_2(p,q) = 0;
		end
	end
end
for p = 1:m
	for q = 1:n
		r = mod(p-1,N4) + 1;
		s = mod(q-1,N4) + 1;
		if fl(p,q) > T4(r,s)
			fl_4(p,q) = 255;
		else
			fl_4(p,q) = 0;
		end
	end
end
for p = 1:m
	for q = 1:n
		r = mod(p-1,N8) + 1;
		s = mod(q-1,N8) + 1;
		if fl(p,q) > T8(r,s)
			fl_8(p,q) = 255;
		else
			fl_8(p,q) = 0;
		end
	end
end

imwrite(fl_2, '../report/house_d2.tif');
imwrite(fl_4, '../report/house_d4.tif');
imwrite(fl_8, '../report/house_d8.tif');

rmse_2 = sqrt((1 / (n * m)) * sum(sum((double(fg) - fl_2).^2)));
rmse_4 = sqrt((1 / (n * m)) * sum(sum((double(fg) - fl_4).^2)));
rmse_8 = sqrt((1 / (n * m)) * sum(sum((double(fg) - fl_8).^2)));

fid_2 = fidelity(double(fg), fl_2);
fid_4 = fidelity(double(fg), fl_4);
fid_8 = fidelity(double(fg), fl_8);
