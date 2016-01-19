#include <math.h>
#include "tiff.h"
#include "allocate.h"
#include "randlib.h"
#include "typeutil.h"

#define FH 9
#define FW 9

void error(char *name);
struct TIFF_img conv2d(struct TIFF_img input_img, int fh, int fw, int **filter);

int main (int argc, char **argv) 
{
	FILE *fp;
	struct TIFF_img input_img, output_img;
	int32_t i,j,m,n,r,c;
	double lpf[FH][FW];
	double rtemp, gtemp, btemp;

	int hlim = (FH - 1) / 2;
	int wlim = (FW - 1) / 2;

	for (i = 0; i < FH; i++) {
		for (j = 0; j < FW; j++) {
			lpf[i][j] = 1.0 / 81;
		}
	}

	if (argc != 2) error(argv[0]);

	/* open image file */
	if ((fp = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "cannot open file %s\n", argv[1]);
		exit(1);
	}

	/* read image */
	if (read_TIFF(fp, &input_img)) {
		fprintf(stderr, "error reading file %s\n", argv[1]);
		exit(1);
	}
	
	int ih = input_img.height;
	int iw = input_img.width;

	/* close image file */
	fclose(fp);

	/* check the type of image data */
	if (input_img.TIFF_type != 'c') {
		fprintf(stderr, "error:  image must be 24-bit color\n");
		exit(1);
	}

	/* set up structure for output color image */
	get_TIFF(&output_img, input_img.height, input_img.width, 'c');
	
	for (i = 0; i < ih; i++) {
		for (j = 0; j < iw; j++) {
			rtemp = 0.0;
			gtemp = 0.0;
			btemp = 0.0;
			for (m = -hlim; m <= hlim; m++) {
				for (n = -wlim; n <= wlim; n++) {
					r = i-m;
					c = j-n;
					if (r < ih && r >=0 && c < iw && c >= 0) {
						rtemp += lpf[m+hlim][n+wlim] * input_img.color[0][r][c]; 
						gtemp += lpf[m+hlim][n+wlim] * input_img.color[1][r][c]; 
						btemp += lpf[m+hlim][n+wlim] * input_img.color[2][r][c]; 
					}
				}
			}
		  	output_img.color[0][i][j] = (int)rtemp;
		  	output_img.color[1][i][j] = (int)gtemp;
		  	output_img.color[2][i][j] = (int)btemp;
		}
	}

	/* open color image file */
	if ((fp = fopen("output-firlpf.tif", "wb")) == NULL) {
		fprintf(stderr, "cannot open file output.tif\n");
		exit(1);
	}

	/* write color image */
	if(write_TIFF(fp, &output_img)) {
		fprintf(stderr, "error writing TIFF file %s\n", argv[2]);
		exit(1);
	}

	/* close color image file */
	fclose(fp);

	/* de-allocate space which was used for the images */
	free_TIFF(&(input_img));
	free_TIFF(&(output_img));

	return(0);
}

struct TIFF_img conv2d(struct TIFF_img input_img, int fh, int fw, int **filter) {
	int hl = (fh - 1) / 2;
	int wl = (fw - 1) / 2;
	int ih = input_img.height;
	int iw = input_img.width;
	uint32_t i,j,m,n,r,c;
	double rt, gt, bt;
	struct TIFF_img output_img;

	get_TIFF(&output_img, ih, iw, 'c');

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
						rt += filter[m+hl][n+wl] * input_img.color[0][r][c]; 
						gt += filter[m+hl][n+wl] * input_img.color[1][r][c]; 
						bt += filter[m+hl][n+wl] * input_img.color[2][r][c]; 
					}
				}
			}
		  	output_img.color[0][i][j] = (int)rt;
		  	output_img.color[1][i][j] = (int)gt;
		  	output_img.color[2][i][j] = (int)bt;
		}
	}
	
	return output_img;
}

void error(char *name)
{
    printf("usage:  %s  image.tiff \n\n",name);
    printf("this program reads in a 24-bit color TIFF image.\n");
    printf("It then horizontally filters the green component, adds noise,\n");
    printf("and writes out the result as an 8-bit image\n");
    printf("with the name 'green.tiff'.\n");
    printf("It also generates an 8-bit color image,\n");
    printf("that swaps red and green components from the input image");
    exit(1);
}
