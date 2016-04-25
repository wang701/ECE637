#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* routines in JPEG_encode.c */
void jpeg_encode(int **img, int h, int w, FILE *jpgp);
void change_qtable(double scale);
int **get_arguments(int   argc,
                   char   *argv[],
                   int    *row,
                   int    *col,
                   double *gamma,
                   FILE  **fp );
void usage(void);



/* routines in JPEGutil.c */
void put_header(
  int width,        /* number of columns in image */
  int height,       /* number of rows in image */
  int quant[8][8],  /* 8x8 quantization matrix */
  FILE * fileout);
void put_tail(FILE * fileout);



/* routines in JPEGutil2.c */
int BitSize(int value);
void VLI_encode(int bitsz, int value, char *block_code);
void ZigZag(int ** img, int y, int x, int *zigline);
void DC_encode(int dc_value, int prev_value, char *block_code);
void AC_encode(int *zigzag, char *block_code);
void Block_encode(int prev_value, int *zigzag, char *block_code);
int Convert_encode(char *block_code, unsigned char *byte_code);
unsigned char Zero_pad(char *block_code);


