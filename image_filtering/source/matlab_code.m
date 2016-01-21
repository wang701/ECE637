u = -pi:0.1:pi;
v = -pi:0.1:pi;

% Section 3 %
[U,V] = meshgrid(u,v);
H_lpf = (1/81)*sin(4.5*U).*sin(4.5*V)./(sin(0.5*U).*sin(0.5*V));
fig1 = figure(1);
surf(U,V,abs(H_lpf));
xlabel('\mu');
ylabel('\nu');
zlabel('H(e^{j\mu},e^{j\nu})');
print(fig1,'lpfcsft','-depsc','-tiff');

% Section 4 %
lamda = 1.5;
H_lpf_1 = (1/25)*sin(2.5*U).*sin(2.5*V)./(sin(0.5*U).*sin(0.5*V));
fig2 = figure(2);
surf(U,V,abs(H_lpf_1));
xlabel('\mu');
ylabel('\nu');
zlabel('H(e^{j\mu},e^{j\nu})');
print(fig2,'lpf1csft','-depsc','-tiff');
G = 1 + lamda*(1 - H_lpf_1);
fig3 = figure(3);
surf(U,V,abs(G));
xlabel('\mu');
ylabel('\nu');
zlabel('G(e^{j\mu},e^{j\nu})');
print(fig3,'hpfcsft','-depsc','-tiff');

% Section 5 %
H_iif = 0.01./(1-0.9*exp(-i*U)-0.9*exp(-i*V)+0.81*exp(-i*(U+V)));
fig4 = figure(4);
surf(U,V,abs(H_iif));
xlabel('\mu');
ylabel('\nu');
zlabel('H(e^{j\mu},e^{j\nu})');
print(fig4,'iircsft','-depsc','-tiff');

x = zeros(256,256);
y = zeros(256,256);
x(128,128) = 1;

for m = 1:256
	for n = 1:256
		y(m,n) = 0.01*x(m,n);
		if (m > 1)
			y(m,n) = y(m,n) + 0.9*y(m-1,n);
		end
		if (n > 1)
			y(m,n) = y(m,n) + 0.9*y(m,n-1);
		end
		if (m > 1 && n > 1)
			y(m,n) = y(m,n) - 0.81*y(m-1,n-1);
		end
	end
end

y(y(:) > 255) = 255;
y(y(:) < 0) = 0;

imwrite(uint8(255*100*y),'h_out.tif');
