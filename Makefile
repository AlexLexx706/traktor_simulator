
CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lX11 -lGL -lGLU -lglut

all: main
	
main: test.o file_reader.o
	$(CC) -o main test.o file_reader.o $(LDFLAGS)

test.o:
	$(CC) $(CFLAGS) simulator/test.cpp

file_reader.o:
	$(CC) $(CFLAGS) simulator/reader/file_reader/file_reader.cpp

clean:
	rm -rf *.o main