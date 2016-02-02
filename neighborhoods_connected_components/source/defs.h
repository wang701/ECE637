#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#include "typeutil.h"
#include "tiff.h"

struct pixel {
	int m;
	int n;
};

struct pixelList {
	struct pixel pixel;
	struct pixelList *next;
};

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

#endif /* _DEFS_H */
