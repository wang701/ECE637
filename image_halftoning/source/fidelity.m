function [fid] = fidelity(f,b)
	f = double(f);
	b = double(b);

	fl = 255 * (f / 255).^2.2;

	sigma = 2;
	[I J] = meshgrid(-3:1:3, -3:1:3);
	h = exp(-(I.^2 + J.^2)/2/sigma);
	h = h / sum(h(:));

	flh = conv2(fl, h, 'same');
	blh = conv2(b, h, 'same');

	flt = 255 * (flh / 255).^(1/3);
	blt = 255 * (blh / 255).^(1/3);

	[m, n] = size(flt);

	fid = sqrt((1 / (n * m)) * sum(sum((flt - blt).^2)));

end
