#include "defs.h"

void ConnectedNeighbors(
	struct pixel s,
	double T,
	unsigned char **img,
	int width,
	int height,
	int *M,
	struct pixel c[4]);

void ConnectedSet(
	struct pixel s,
	double T,
	unsigned char **img,
	int width,
	int height,
	int ClassLabel,
	unsigned int **seg,
	int *NumConPixels);

void ConnectedNeighbors(
	struct pixel s,
	double T,
	unsigned char **img,
	int width,
	int height,
	int *M,
	struct pixel c[4]) {
	*M = 0;

	if ((s.n-1) >= 0 && abs(img[s.m][s.n] - img[s.m][s.n-1]) <= T) {
		c[*M].m = s.m;
		c[*M].n = s.n - 1;
		(*M)++;
	}
	if ((s.n+1) < width && abs(img[s.m][s.n] - img[s.m][s.n+1]) <= T) {
		c[*M].m = s.m;
		c[*M].n = s.n + 1;
		(*M)++;
	}
	if ((s.m-1) >= 0 && abs(img[s.m][s.n] - img[s.m-1][s.n]) <= T) {
		c[*M].m = s.m - 1;
		c[*M].n = s.n;
		(*M)++;
	}
	if ((s.m+1) < height && abs(img[s.m][s.n] - img[s.m+1][s.n]) <= T) {
		c[*M].m = s.m + 1;
		c[*M].n = s.n;
		(*M)++;
	}
}

void ConnectedSet(
	struct pixel s,
	double T,
	unsigned char **img,
	int width,
	int height,
	int ClassLabel,
	unsigned int **seg,
	int *NumConPixels) {
	struct pixelList *top, *bottom, *tmp;
	struct pixel c[4];
	int M = 0;
	int i;

	(*NumConPixels) = 0;
	top = (struct pixelList *)malloc(sizeof(struct pixelList));
	tmp = (struct pixelList *)malloc(sizeof(struct pixelList));
	top->pixel.m = s.m;
	top->pixel.n = s.n;
	top->next = NULL;
	bottom = top;

	while (top != NULL) {
		if (seg[top->pixel.m][top->pixel.n] != ClassLabel) {
			seg[top->pixel.m][top->pixel.n] != ClassLabel;
			(*NumConPixels)++;
			ConnectedNeighbors(top->pixel, T, img, width, height, &M, c);

			for (i = 0; i < M; i++) {
				if (seg[c[i].m][c[i].n] != ClassLabel) {
					tmp->pixel.m = c[i].m;
					tmp->pixel.n = c[i].n;
					tmp->next = NULL;

					bottom->next = tmp;
					bottom = tmp;
				}
			}
		}

		tmp = top->next;
		free(top);
		top = tmp;
	}
}

