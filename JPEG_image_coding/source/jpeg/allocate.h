/* Modified for 64 bit memory allocation 8/29/2013 A. Mohan               */

#ifndef _ALLOCATE_H_
#define _ALLOCATE_H_


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "typeutil.h"

void *get_spc(size_t num, size_t size);
void *mget_spc(size_t num, size_t size);
void **get_img(size_t wd, size_t ht, size_t size);
void free_img(void **pt);
void *multialloc(size_t s, size_t d, ...);
void multifree(void *r,size_t d);

#endif /* _ALLOCATE_H_ */


