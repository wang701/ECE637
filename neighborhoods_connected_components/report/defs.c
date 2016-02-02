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
	struct pixelList *head, *tail, *tmp;
	struct pixel c[4];
	int M, i;

	(*NumConPixels) = 0;
	head = (struct pixelList *)malloc(sizeof(struct pixelList));
	head->pixel.m = s.m;
	head->pixel.n = s.n;
	head->next = NULL;
	tail = head;

	/****************************************************
     * start with the chosen pixel
     * build a linked list of the pixel that is not yet
     * labeled, the next starting pixel will be the head
     * of the built linked list
     ***************************************************/

	while (head != NULL) {
		if (seg[head->pixel.m][head->pixel.n] != ClassLabel) {
			seg[head->pixel.m][head->pixel.n] = ClassLabel;
			(*NumConPixels)++;
            // find the connected neighbors (not-yet labled)
			ConnectedNeighbors(head->pixel, T, img, width, height, &M, c);

            // go through the neighbors, build the linked list
			for (i = 0; i < M; i++) {
				if (seg[c[i].m][c[i].n] != ClassLabel) {
					tmp = (struct pixelList *)malloc(sizeof(struct pixelList));
					tmp->pixel.m = c[i].m;
					tmp->pixel.n = c[i].n;
					tmp->next = NULL;

					tail->next = tmp;
					tail = tmp;
				}
			}
		}

        // new pixel will the linked list head
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

void error(char *name)
{
	printf("Very useful error message.\n\n");
    exit(1);
}

