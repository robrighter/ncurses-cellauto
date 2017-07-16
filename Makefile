CC=g++
CFLAGS=-Wall -std=c++11 -g -ansi -pedantic
LDFLAGS=-lncursesw

OBJECTS=main.o conway.o

cellauto: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o main $(LDFLAGS)

all:cellauto

clean:
	rm -rf *.o *.dSYM main


