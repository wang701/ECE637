# For Linux or any machines with gcc compiler
CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

# For SunOS
#CFLAGS = -Aa

all: medfilter

clean:
	/bin/rm *.o medfilter

OBJ = tiff.o allocate.o randlib.o

medfilter: medfilter.o $(OBJ)
	$(CC) $(CFLAGS) -o medfilter medfilter.o $(OBJ) -lm

