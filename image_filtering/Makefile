# For Linux or any machines with gcc compiler
CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

# For SunOS
#CFLAGS = -Aa

all: Example

clean:
	/bin/rm *.o Example

OBJ = tiff.o allocate.o randlib.o

Example: Example.o $(OBJ) 
	$(CC) $(CFLAGS) -o Example Example.o $(OBJ) -lm

