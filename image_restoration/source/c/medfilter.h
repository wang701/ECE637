#ifndef __MEDFILT_H_
#define __MEDFILT_H_

void error(char *name);
unsigned int filterp(struct TIFF_img in, int i, int j);
unsigned int** filter(struct TIFF_img in);

#endif
