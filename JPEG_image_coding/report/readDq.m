function [img] = readDq(file, gamma)
	run('Qtables.m');
	f = fopen(file, 'r');
	data = fread(f, 'integer*2');
	img = reshape(data(3:end), [data(2) data(1)])';
	img = blockproc(img, [8 8], ...
		@(x) round(idct2(x.data.*Quant*gamma, [8 8])));
	img = img + 128;
	img = uint8(img);
end
