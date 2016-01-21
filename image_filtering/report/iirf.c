#include <math.h>
#include "tiff.h"
#include "allocate.h"
#include "randlib.h"
#include "typeutil.h"
#include "defs.h"

int main (int argc, char **argv) 
{
	FILE *fp;
	struct TIFF_img input_img, output_img;
	int i, j, m, ih, iw;
		
	if (argc != 2) erroriirf(argv[0]);
 
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
 
	/* close image file */
	fclose(fp);

	/* check the type of image data */
	if (input_img.TIFF_type != 'c') {
		fprintf(stderr, "error:  image must be 24-bit color\n");
		exit(1);
	}
	
	/* set up structure for output color image */
	get_TIFF(&output_img, input_img.height, input_img.width, 'c');

	ih = input_img.height;
	iw = input_img.width;
	double ***ct = (double ***)malloc(3 * sizeof(double **));
	for (m = 0; m < 3; m++) {
		ct[m] = (double **)malloc(ih * sizeof(double *));
		for (i = 0; i < ih; i++) {
			ct[m][i] = (double *)malloc(iw * sizeof(double)); 
		}
	}

	/* filter image with IIR filter */
	for (m = 0; m < 3; m++) {
		for (i = 0; i < ih; i++) {
			for (j = 0; j < iw; j++) {
				ct[m][i][j] = 0.01 * input_img.color[m][i][j]; 
				if (i > 0) {
					ct[m][i][j] += 0.9 * ct[m][i-1][j];
				} 
				if (j > 0) {
					ct[m][i][j] += 0.9 * ct[m][i][j-1];
				}
				if (i > 0 && j > 0) {
					ct[m][i][j] += -0.81 * ct[m][i-1][j-1];
				} 
			}
		}
	} // it needs to run until the end

	/* write RGB colors to output image*/
	for (m = 0; m < 3; m++) {
		for (i = 0; i < ih; i++) {
			for (j = 0; j < iw; j++) {
				output_img.color[m][i][j] = constrain(ct[m][i][j]);
			}
		}
	}

	/* open color image file */
	if ((fp = fopen("output-iirf.tif", "wb")) == NULL) {
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

	/* free color temp array */
	for (m = 0; m < 3; m++) {
		for (i = 0; i < ih; i++) {
			free(ct[m][i]);
		}
		free(ct[m]);
	}
	free(ct);
	
	return(0);
}
