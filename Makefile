.PHONY: all clean install uninstall
	
CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lX11 -lGL -lGLU -lglut

all: main
	
main: test.o file_reader.o
	$(CC) -o main test.o file_reader.o $(LDFLAGS)

test.o: simulator/test.cpp 
	$(CC) $(CFLAGS) simulator/test.cpp

file_reader.o: simulator/reader/file_reader/file_reader.cpp simulator/reader/file_reader/file_reader.h simulator/reader/base_reader.h
	$(CC) $(CFLAGS) simulator/reader/file_reader/file_reader.cpp

clean:
	rm -rf *.o main