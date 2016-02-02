#include "defs.h"

int main (int argc, char **argv) {
	FILE *fp;
	struct TIFF_img input_img;
	struct pixel s;
	int i, j, numcon;
	int ClassLabel = 1;
	double T;

	if (argc != 6) error(argv[0]);

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
	if (input_img.TIFF_type != 'g') {
		fprintf(stderr, "error:  image must be grayscale\n");
		exit(1);
	}

	/* get the other parameters */
	sscanf(argv[2], "%d", &(s.m));
	sscanf(argv[3], "%d", &(s.n));
	sscanf(argv[4], "%lf", &T);

	unsigned int **seg = (unsigned int **)get_img(input_img.width,
                                                  input_img.height,
                                                  sizeof(unsigned int));
	ConnectedSet(s, T, input_img.mono, input_img.width, input_img.height,
                 ClassLabel, seg, &numcon);

	for (i = 0; i < input_img.height; i++) {
		for (j = 0; j < input_img.width; j++) {
			if (seg[i][j] == ClassLabel) {
				input_img.mono[i][j] = 0;
			} else {
				input_img.mono[i][j] = 255;
			}
		}
	}

	free_img((void *)seg);

	/* open output image file */
	if ((fp = fopen(argv[5], "wb")) == NULL) {
		fprintf(stderr, "cannot open file output.tif\n");
		exit(1);
	}

	/* write output image */
	if(write_TIFF(fp, &input_img)) {
		fprintf(stderr, "error writing TIFF file %s\n", argv[5]);
		exit(1);
	}

	/* close color image file */
	fclose(fp);

	/* de-allocate space which was used for the images */
	free_TIFF(&(input_img));

	return(0);
}
