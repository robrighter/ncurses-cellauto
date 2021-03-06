CC=g++
CFLAGS=-Wall -std=gnu++11 -g -pedantic -Wc++11-extensions 

LDFLAGS=-lncursesw

OBJECTS=main.o conway.o

cellauto: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o main $(LDFLAGS)

all:cellauto

clean:
	rm -rf *.o *.dSYM main


