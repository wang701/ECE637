#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#include "typeutil.h"
#include "tiff.h"

int constrain(double pixel_color);
void conv2d(struct TIFF_img *iimg, struct TIFF_img *oimg,
			int fh, int fw, double **filter);

#endif /* _DEFS_H */
