#include "defs.h"

void errorlpf(char *name);
int constrain(double pixel_color);
void conv2d(struct TIFF_img *iimg, struct TIFF_img *oimg,
			int fh, int fw, double **filter);

int constrain(double pixel_color) {
	int color = (int)pixel_color;
	if (color > 255) {
		color = 255;
	} else if (color < 0) {
		color = 0;
	}
	return color;
}

void conv2d(struct TIFF_img *iimg, struct TIFF_img *oimg,
			int fh, int fw, double **filter) {
	int hl = (fh - 1) / 2;
	int wl = (fw - 1) / 2;
	int ih = iimg->height;
	int iw = iimg->width;
	int32_t i,j,m,n,r,c;
	double rt, gt, bt;

	for (i = 0; i < ih; i++) {
		for (j = 0; j < iw; j++) {
			rt = 0.0;
			gt = 0.0;
			bt = 0.0;
			for (m = -hl; m <= hl; m++) {
				for (n = -wl; n <= wl; n++) {
					r = i-m;
					c = j-n;
					if (r < ih && r >=0 && c < iw && c >= 0) {
						rt += filter[m+hl][n+wl] * iimg->color[0][r][c];
						gt += filter[m+hl][n+wl] * iimg->color[1][r][c]; 
						bt += filter[m+hl][n+wl] * iimg->color[2][r][c]; 
					}
				}
			}
		  	oimg->color[0][i][j] = constrain(rt);
		  	oimg->color[1][i][j] = constrain(gt);
		  	oimg->color[2][i][j] = constrain(bt);
		}
	}
}

void errorlpf(char *name)
{
    printf("usage:  %s  image.tiff \n\n", name);
    printf("This program reads in a 24-bit color TIFF image.\n");
	printf("It then filters the image with a 9x9 FIR low pass filter.\n\n");
    exit(1);
}

void errorsf(char *name)
{
    printf("usage:  %s  image.tiff lambda\n\n", name);
    printf("This program reads in a 24-bit color TIFF image.\n");
	printf("It then filters the image with a 5x5 FIR sharpening filter,\n");
    printf("with supplied lambda value.\n");
    printf("The greater lambda is, the higher sharpening intensity.\n\n");
    exit(1);
}
