function [Z Y] = equalize(X)
	N = hist(X(:), [0:255]);
	Y = cumsum(N)/sum(N);

	Ymin = Y(min(X(:)));
	Ymax = Y(max(X(:)));

	Z = uint8(255*((Y(X) - Ymin)/(Ymax - Ymin)));
end
