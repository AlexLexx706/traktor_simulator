.PHONY: all clean install uninstall
	
CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lX11 -lGL -lGLU -lglut

all: main
	
main: test.o file_reader.o SMat.o base_item.o
	$(CC) -o main test.o file_reader.o SMat.o $(LDFLAGS)

test.o: simulator/test.cpp  
	$(CC) $(CFLAGS) simulator/test.cpp

SMat.o: simulator/common/SMat.h simulator/common/SMat.cc 
	$(CC) $(CFLAGS) simulator/common/SMat.cc

base_item.o: simulator/items/base_item.h simulator/items/base_item.cpp 
	$(CC) $(CFLAGS) simulator/items/base_item.cpp


file_reader.o: simulator/reader/file_reader/file_reader.cpp simulator/reader/file_reader/file_reader.h simulator/reader/base_reader.h
	$(CC) $(CFLAGS) simulator/reader/file_reader/file_reader.cpp

clean:
	rm -rf *.o main