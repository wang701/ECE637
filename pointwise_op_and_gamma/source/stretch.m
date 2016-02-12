function [output] = stretch(input, T1, T2)
	output = zeros(size(input));

	index = find(input > T1 & input < T2);
	output(index) = (input(index) - T1)*(255/(T2-T1));
	output(input > T2) = 255;

	output = uint8(output);
