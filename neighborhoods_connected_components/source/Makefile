# For Linux or any machines with gcc compiler
CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -g

# For SunOS
#CFLAGS = -Aa

all: areafill segmen

clean:
	/bin/rm -f *.o area_fill segmen

OBJ = defs.o tiff.o allocate.o randlib.o

areafill: area_fill.o $(OBJ)
	$(CC) $(CFLAGS) -o area_fill area_fill.o $(OBJ) -lm

segmen: segmen.o $(OBJ)
	$(CC) $(CFLAGS) -o segmen segmen.o $(OBJ) -lm
