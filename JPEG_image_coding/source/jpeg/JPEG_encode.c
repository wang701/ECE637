/*******************************************************/
/* JPEG_encoder    By Jinwha Yang and Charles Bouman   */
/* Apr. 2000.      Built for EE637 Lab.                */
/* All right reserved for Prof. Bouman                 */
/*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Htables.h"
#include "JPEGdefs.h"
#include "allocate.h"



int main(int argc, char* argv[])
{
  int  **input_img;  /* Input set of DCT coefficients read from matlab file */
  FILE  *outfp;      /* File pointer to output JPEG image */
  int    row;        /* height of image */
  int    column;     /* width of image */
  double gamma;      /* scaling factor for quantizer */

  /* Use command line arguements to read matlab file, and return */
  /* values of height, width, quantizer scaling and file pointer */
  /* to output JPEG file.                                        */
  input_img = get_arguments(argc,argv,&row,&column,&gamma,&outfp) ;

  /* scale global variable for quantization matrix */
  if( gamma > 0 )
    change_qtable(gamma) ;
  else {
    fprintf(stderr, "\nQuantizer scaling must be > 0.\n") ;
    exit(-1) ;
  }

  /* Encode quantized DCT coefficients into JPEG image */
  jpeg_encode(input_img,row,column,outfp) ;

  return 1 ;
}


void change_qtable(double scale)
{
  int     i,j ;
  double  val ;

  for(i=0;i<8;i++){
    for(j=0;j<8;j++){
      val = Quant[i][j]*scale ;
      /* w.r.t spec, Quant entry can be bigger than 16 bit */
      Quant[i][j] = (val>65535) ? 65535 : (int)(val+0.5) ;
    }
  }
}


int **get_arguments(int argc,
		   char *argv[],
		   int *row,
		   int *col,
		   double *gamma,
		   FILE **fp )
{
  FILE *   inp ;
  short**  img ;
  int  **  in_img ;
  short    tmp ;
  int      i,j ;


  /* needs at least 2 argument */
  switch(argc){
  case 0:
  case 1:
  case 2:
  case 3: usage(); exit(-1) ; break ;
  default:

    /* read Quant scale */
    sscanf(argv[1],"%lf",gamma) ;

    /* prepare output file */
    *fp = fopen(argv[3],"wb") ;
    if(*fp==NULL) {
      fprintf(stderr,
	    "\n%s file error\n",argv[3]) ;
      exit(-1) ;
    }

    /* read input file */
    inp = fopen(argv[2],"rb") ;
    if( inp == NULL ) {
      fprintf(stderr,
	      "\n%s open error\n",argv[2]) ;
      exit(-1) ;
    }
    /* input file has 2 16 bit(short) row, column info */
    /* valid 2-D array follows */
    fread(&tmp,sizeof(short),1,inp) ;
    *row = (int) tmp ;
    fread(&tmp,sizeof(short),1,inp) ;
    *col = (int) tmp ;

    img = (short **)get_img(*col,*row,sizeof(short)) ;
    fread(img[0],sizeof(short),*col**row,inp) ;
    fclose(inp) ;

    break ;
  }

  in_img = (int **)get_img(*col,*row,sizeof(int)) ;
  for( i=0 ; i<*row; i++ ){
    for( j=0 ; j<*col; j++ ){
      in_img[i][j] = (int) img[i][j] ;
    }
  }
  free_img((void**)img) ;
  return( in_img ) ;
}



void jpeg_encode(int **img, int h, int w, FILE *jpgp)
{
  int    x, y, length ;
  int    prev_dc = 0 ;
  unsigned char val ;
  static int    zigline[64] ;
  static char   block_code[8192] = {0} ;
  static unsigned char byte_code[1024] ;

  printf("\n JPEG encode starts...") ;
  /* JPEG header writes */
  put_header(w,h,Quant,jpgp) ;

  printf("\n Header written...\n Image size %d row  %d column\n",h,w) ;
  /* Normal block processing */
  for( y = 0 ; y < h ; y += 8) {
    for( x = 0 ; x < w ; x += 8 ){
      /* read up 8x8 block */
      ZigZag(img,y,x,zigline) ;
      Block_encode(prev_dc,zigline,block_code) ;
      prev_dc = zigline[0] ;
      length = Convert_encode(block_code,byte_code) ;
      fwrite(byte_code,sizeof(char),length,jpgp) ;
    }
    printf("\r (%d)th row processing   ",y) ;
  }
  printf("\nEncode done.\n") ;
  /* Zero padding */
  if( strlen(block_code) ){
    val = Zero_pad(block_code) ;
    fwrite(&val,sizeof(char),1,jpgp) ;
  }

  /* EOI */
  put_tail(jpgp) ;
  fclose(jpgp) ;
  free_img((void **)img) ;
}



void usage(void)
{
  fprintf(stderr,"\nJPEG_encode <Quant scale> <in_file> <out_file>");
  fprintf(stderr,"\n<Quant scale> - gamma value in eq (1)");
  fprintf(stderr,"\n<in_file> - output file using section 2.1");
  fprintf(stderr,"\n<out_file> - JPEG output file\n");
}


