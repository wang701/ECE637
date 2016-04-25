# For Linux or any machines with gcc compiler
CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -g

# For SunOS
#CFLAGS = -Aa

all: JPEG_encode

clean:
	/bin/rm -f *.o JPEG_encode

OBJ = JPEGdefs.o JPEGutil.o allocate.o

JPEG_encode: JPEG_encode.o $(OBJ)
	$(CC) $(CFLAGS) -o JPEG_encode JPEG_encode.o $(OBJ) -lm
