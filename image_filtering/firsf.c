#include <math.h>
#include "tiff.h"
#include "allocate.h"
#include "randlib.h"
#include "typeutil.h"
#include "defs.h"

#define FH 5 
#define FW 5

int main (int argc, char **argv) 
{
	FILE *fp;
	struct TIFF_img input_img, output_img;
	int i, j;
	double lamda;
	double delta;
	char *lamdastr;
		
	if (argc != 3) errorsf(argv[0]);

	lamda = strtod(argv[2], &lamdastr);

	double *sf[FH];
	for (i = 0; i < FH; i++) {
		sf[i] = (double *)malloc(FW * sizeof(double));
	}

	for (i = 0; i < FH; i++) {
		for(j = 0; j < FW; j++) {
			if(i == 2 && j == 2) {
				delta = 1.0;
			} // m = n = 0
			else {
				delta = 0.0;
			}
			sf[i][j] = delta + lamda * (delta-1.0/25.0);
		}
	}

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
	
	/* filter the image with lpf */
	conv2d(&input_img, &output_img, FH, FW, sf);	

	/* open color image file */
	if ((fp = fopen("output-firsf.tif", "wb")) == NULL) {
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

	/* free filter array */
	for (i = 0; i < FW; i++) {
		free(sf[i]);
	}
	
	return(0);
}
