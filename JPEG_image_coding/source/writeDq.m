function writeDq(file, img, gamma)
	run('Qtables.m');
	img = double(img) - 128;
	dct_blk = blockproc(img, [8 8], ...
		@(x) round(dct2(x.data, [8 8])./(Quant*gamma)));

	f = fopen(file, 'w');
	fwrite(f, size(dct_blk, 1), 'integer*2');
	fwrite(f, size(dct_blk, 2), 'integer*2');
	fwrite(f, dct_blk', 'integer*2');
end
