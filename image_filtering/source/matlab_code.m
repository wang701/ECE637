u = -pi:0.001:pi;
v = -pi:0.001:pi;
H1 = 0;
H2 = 0;

for m = -4:4
	H1 = H1 + exp((-i)*u*m);
end
for n = -4:4
	H2 = H2 + exp((-i)*v*n);
end
H = H1.*H2;
