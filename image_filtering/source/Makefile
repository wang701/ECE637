# For Linux or any machines with gcc compiler
CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

# For SunOS
#CFLAGS = -Aa

all: firlpf firsf 

clean:
	/bin/rm -f *.o firlpf firsf

OBJ = defs.o tiff.o allocate.o randlib.o

firlpf: firlpf.o $(OBJ) 
	$(CC) $(CFLAGS) -o firlpf firlpf.o $(OBJ) -lm

firsf: firsf.o $(OBJ) 
	$(CC) $(CFLAGS) -o firsf firsf.o $(OBJ) -lm

