#include "defs.h"

int main (int argc, char **argv) {
	FILE *fp;
	struct TIFF_img input_img;
	struct pixel s;
	int i, j, numcon, segLabel;
	double T;

	if (argc != 4) error(argv[0]);

	/* we have 1 segment at the beginning */
	segLabel = 1;

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
	sscanf(argv[2], "%lf", &T);

	unsigned int **seg = (unsigned int **)get_img(input_img.width,
                                                  input_img.height,
                                                  sizeof(unsigned int));

    /* make sure all elements are 0 */
    for (i = 0; i < input_img.height; i++) {
		for (j = 0; j < input_img.width; j++) {
			seg[i][j] = 0;
		}
	}

    /* go through the image */
	for (i = 0; i < input_img.height; i++) {
		for (j = 0; j < input_img.width; j++) {
			if (seg[i][j] == 0) {
				s.m = i;
				s.n = j;
				ConnectedSet(s, T, input_img.mono, input_img.width,
                             input_img.height, segLabel, seg, &numcon);
				if (numcon > 100) {
                    /* new label created after 100 connected sets */
					segLabel++;
				} else {
                    /* otherwise, back to 0 */
					ConnectedSet(s, T, input_img.mono, input_img.width,
                                 input_img.height, 1, seg, &numcon);
				}
			}
		}
	}

	printf("Number of regions generated for %lf is %d\n", T, segLabel - 1);

	for (i = 0; i < input_img.height; i++) {
		for (j = 0; j < input_img.width; j++) {
			input_img.mono[i][j] = seg[i][j];
		}
	}

	free_img((void *)seg);

	/* open output image file */
	if ((fp = fopen(argv[3], "wb")) == NULL) {
		fprintf(stderr, "cannot open file output.tif\n");
		exit(1);
	}

	/* write output image */
	if(write_TIFF(fp, &input_img)) {
		fprintf(stderr, "error writing TIFF file %s\n", argv[3]);
		exit(1);
	}

	/* close color image file */
	fclose(fp);

	/* de-allocate space which was used for the images */
	free_TIFF(&(input_img));

	return(0);
}
