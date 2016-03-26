#include <math.h>
#include <string.h>

#include "tiff.h"
#include "allocate.h"
#include "medfilter.h"

int main (int argc, char **argv) {
	FILE *fp;
	struct TIFF_img tiff;
	unsigned int** filtered;
	int i, j;

	if (argc != 3) {
		error(argv[0]);
	}

	/* open image file */
	if ((fp = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "cannot open file %s\n", argv[1]);
		exit(1);
	}

	/* read image */
	if (read_TIFF(fp, &tiff)) {
		fprintf(stderr, "error reading file %s\n", argv[1]);
		exit(1);
	}

	/* close image file */
	fclose(fp);

	/* check the type of image data */
	if (tiff.TIFF_type != 'g') {
		fprintf(stderr, "error: image must be grayscale\n");
		exit(1);
	}

	filtered = filter(tiff);
	for (i = 0; i < tiff.height; i++) {
		for (j = 0; j < tiff.width; j++) {
		tiff.mono[i][j] = filtered[i][j];
		}
	}

	/* Free segment map */
	free_img((void *)filtered);

	/* open image file */
	if ((fp = fopen(argv[2], "wb")) == NULL) {
		fprintf(stderr, "cannot open file %s\n", argv[3]);
		exit(1);
	}

	/* write image */
	if (write_TIFF(fp, &tiff)) {
		fprintf(stderr, "error writing TIFF file %s\n", argv[3] );
		exit(1);
	}

	/* close image file */
	fclose(fp);

	/* de-allocate space which was used for the tiff */
	free_TIFF(&tiff);

	return(0);
}

void error(char *name) {
    printf("usage:  %s image.tiff output.tiff\n\n", name);
	printf("Filter an image with a weighted median fitler\n");
    exit(1);
}

unsigned int filterp(struct TIFF_img in, int i, int j) {
	int m, n, k;
	unsigned int sum1, sum2;
	unsigned int tmp;
	unsigned int data[25];
	unsigned int weights[25] = {1, 1, 1, 1, 1,
								1, 2, 2, 2, 1,
								1, 2, 2, 2, 1,
								1, 2, 2, 2, 1,
								1, 1, 1, 1, 1};

	k = 0;
	for (m = i - 2; m < i + 3; m++) {
		for (n = j - 2; n < j + 3; n++) {
			data[k] = in.mono[m][n];
			k++;
		}
	}

	for (m = 0; m < 25; m++) {
		for (n = m + 1; n < 25; n++) {
			if (data[m] < data[n]) {
				tmp = data[m];
				data[m] = data[n];
				data[n] = tmp;

				tmp = weights[m];
				weights[m] = weights[n];
				weights[n] = tmp;
			}
		}
	}

	sum1 = weights[0];
	sum2 = 34 - sum1;
	for (m = 0; m < 25; m++) {
		if (sum1 > sum2) {
			return data[m];
		}

		sum1 += weights[m+1];
		sum2 -= weights[m+1];
	}

	return data[m];
}

unsigned int** filter(struct TIFF_img in) {
	int i, j;

	unsigned int** filtered = (unsigned int**) get_img(in.width,
														in.height,
														sizeof(unsigned int));
	for (i = 2; i < in.height - 2; i++) {
		for (j = 2; j < in.width - 2; j++) {
			filtered[i][j] = filterp(in, i, j);
		}
	}

	return filtered;
}
