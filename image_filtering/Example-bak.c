
#include <math.h>
#include "tiff.h"
#include "allocate.h"
#include "randlib.h"
#include "typeutil.h"

void error(char *name);

int main (int argc, char **argv) 
{
  FILE *fp;
  struct TIFF_img input_img, green_img, color_img;
  double **img1,**img2;
  int32_t i,j,pixel;

  if ( argc != 2 ) error( argv[0] );

  /* open image file */
  if ( ( fp = fopen ( argv[1], "rb" ) ) == NULL ) {
    fprintf ( stderr, "cannot open file %s\n", argv[1] );
    exit ( 1 );
  }

  /* read image */
  if ( read_TIFF ( fp, &input_img ) ) {
    fprintf ( stderr, "error reading file %s\n", argv[1] );
    exit ( 1 );
  }

  /* close image file */
  fclose ( fp );

  /* check the type of image data */
  if ( input_img.TIFF_type != 'c' ) {
    fprintf ( stderr, "error:  image must be 24-bit color\n" );
    exit ( 1 );
  }

  /* Allocate image of double precision floats */
  img1 = (double **)get_img(input_img.width,input_img.height,sizeof(double));
  img2 = (double **)get_img(input_img.width,input_img.height,sizeof(double));

  /* copy green component to double array */
  for ( i = 0; i < input_img.height; i++ )
  for ( j = 0; j < input_img.width; j++ ) {
    img1[i][j] = input_img.color[1][i][j];
  }

  /* Filter image along horizontal direction */
  for ( i = 0; i < input_img.height; i++ )
  for ( j = 1; j < input_img.width-1; j++ ) {
    img2[i][j] = (img1[i][j-1] + img1[i][j] + img1[i][j+1])/3.0;
  }

  /* Fill in boundary pixels */
  for ( i = 0; i < input_img.height; i++ ) {
    img2[i][0] = 0;
    img2[i][input_img.width-1] = 0;
  }

  /* Set seed for random noise generator */
  srandom2(1);

  /* Add noise to image */
  for ( i = 0; i < input_img.height; i++ )
  for ( j = 1; j < input_img.width-1; j++ ) {
    img2[i][j] += 32*normal();
  }

  /* set up structure for output achromatic image */
  /* to allocate a full color image use type 'c' */
  get_TIFF ( &green_img, input_img.height, input_img.width, 'g' );
    
  /* set up structure for output color image */
  /* Note that the type is 'c' rather than 'g' */
  get_TIFF ( &color_img, input_img.height, input_img.width, 'c' );

  /* copy green component to new images */
  for ( i = 0; i < input_img.height; i++ )
  for ( j = 0; j < input_img.width; j++ ) {
    pixel = (int32_t)img2[i][j];
    if(pixel>255) {
      green_img.mono[i][j] = 255;
    }
    else {
      if(pixel<0) green_img.mono[i][j] = 0;
      else green_img.mono[i][j] = pixel;
    }
  }

  /* Illustration: constructing a sample color image -- interchanging the red and green components from the input color image */
  for ( i = 0; i < input_img.height; i++ )
      for ( j = 0; j < input_img.width; j++ ) {
          color_img.color[0][i][j] = input_img.color[1][i][j];
          color_img.color[1][i][j] = input_img.color[0][i][j];
          color_img.color[2][i][j] = input_img.color[2][i][j];
      }

  /* open green image file */
  if ( ( fp = fopen ( "green.tif", "wb" ) ) == NULL ) {
    fprintf ( stderr, "cannot open file green.tif\n");
    exit ( 1 );
  }

  /* write green image */
  if ( write_TIFF ( fp, &green_img ) ) {
    fprintf ( stderr, "error writing TIFF file %s\n", argv[2] );
    exit ( 1 );
  }

  /* close green image file */
  fclose ( fp );
    
    
  /* open color image file */
  if ( ( fp = fopen ( "color.tif", "wb" ) ) == NULL ) {
      fprintf ( stderr, "cannot open file color.tif\n");
      exit ( 1 );
  }
    
  /* write color image */
  if ( write_TIFF ( fp, &color_img ) ) {
      fprintf ( stderr, "error writing TIFF file %s\n", argv[2] );
      exit ( 1 );
  }
    
  /* close color image file */
  fclose ( fp );

  /* de-allocate space which was used for the images */
  free_TIFF ( &(input_img) );
  free_TIFF ( &(green_img) );
  free_TIFF ( &(color_img) );
  
  free_img( (void**)img1 );
  free_img( (void**)img2 );  

  return(0);
}

void error(char *name)
{
    printf("usage:  %s  image.tiff \n\n",name);
    printf("this program reads in a 24-bit color TIFF image.\n");
    printf("It then horizontally filters the green component, adds noise,\n");
    printf("and writes out the result as an 8-bit image\n");
    printf("with the name 'green.tiff'.\n");
    printf("It also generates an 8-bit color image,\n");
    printf("that swaps red and green components from the input image");
    exit(1);
}

