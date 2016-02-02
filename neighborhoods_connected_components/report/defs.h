#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#include "tiff.h"
#include "allocate.h"
#include "randlib.h"
#include "typeutil.h"
#include "typeutil.h"

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

void error(char *name);

#endif /* _DEFS_H */
