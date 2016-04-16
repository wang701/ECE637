function [out] = errDiffusion(in)
	inl = 255 * (double(in) / 255).^2.2;
	out = padarray(inl, [1 1]);

	for i = 2:size(out,1) - 1
		for j = 2:size(out,2) - 1
			orig = out(i,j);
			out(i,j) = (out(i,j) > 127) * 255;
			e = orig - out(i,j);
			out(i,j+1) = out(i,j+1) + e*(7/16);
			out(i+1,j+1) = out(i+1,j+1) + e*(1/16);
			out(i+1,j) = out(i+1,j) + e*(5/16);
			out(i+1,j-1) = out(i+1,j-1) + e*(3/16);
		end
	end

	out = out(2:end-1, 2:end-1);

end
