# For Linux or any machines with gcc compiler
CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -g

# For SunOS
#CFLAGS = -Aa

all: firlpf firsf iirf 

clean:
	/bin/rm -f *.o firlpf firsf iirf

OBJ = defs.o tiff.o allocate.o randlib.o

firlpf: firlpf.o $(OBJ) 
	$(CC) $(CFLAGS) -o firlpf firlpf.o $(OBJ) -lm

firsf: firsf.o $(OBJ) 
	$(CC) $(CFLAGS) -o firsf firsf.o $(OBJ) -lm

iirf: iirf.o $(OBJ) 
	$(CC) $(CFLAGS) -o iirf iirf.o $(OBJ) -lm
