.PHONY: all clean install uninstall
	
CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lX11 -lGL -lGLU -lglut
OBJS=main.o coordinat_converter.o file_reader.o SMat.o base_shape.o box.o scene.o tractor.o camera.o

all: main
	
main: $(OBJS)
	$(CC) -o main $(OBJS) $(LDFLAGS)

main.o: simulator/main.cpp  
	$(CC) $(CFLAGS) simulator/main.cpp

SMat.o: simulator/common/SMat.h simulator/common/SMat.cc 
	$(CC) $(CFLAGS) simulator/common/SMat.cc

coordinat_converter.o: simulator/common/coordinat_converter/coordinat_converter.h simulator/common/coordinat_converter/coordinat_converter.cpp simulator/common/SMat.h
	$(CC) $(CFLAGS) simulator/common/coordinat_converter/coordinat_converter.cpp

base_shape.o: simulator/engine/shapes/base_shape.h simulator/engine/shapes/base_shape.cpp 
	$(CC) $(CFLAGS) simulator/engine/shapes/base_shape.cpp

box.o: simulator/engine/shapes/base_shape.h simulator/engine/shapes/box/box.h simulator/engine/shapes/box/box.cpp 
	$(CC) $(CFLAGS) simulator/engine/shapes/box/box.cpp

tractor.o: simulator/engine/shapes/base_shape.h simulator/engine/tractor/tractor.h simulator/engine/tractor/tractor.cpp 
	$(CC) $(CFLAGS) simulator/engine/tractor/tractor.cpp

camera.o: simulator/engine/shapes/base_shape.h simulator/engine/camera/camera.h simulator/engine/camera/camera.cpp 
	$(CC) $(CFLAGS) simulator/engine/camera/camera.cpp


scene.o: simulator/engine/scene/scene.h simulator/engine/scene/scene.cpp simulator/engine/shapes/base_shape.h 
	$(CC) $(CFLAGS) simulator/engine/scene/scene.cpp


file_reader.o: simulator/reader/file_reader/file_reader.cpp simulator/reader/file_reader/file_reader.h simulator/reader/base_reader.h
	$(CC) $(CFLAGS) simulator/reader/file_reader/file_reader.cpp

clean:
	rm -rf *.o main