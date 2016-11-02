#include <GL/glut.h>
#include "reader/base_reader.h"
#include "reader/file_reader/file_reader.h"
#include <iostream>

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void Initialize() {
    glClearColor(0.8, 1.0, 0.6, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-200.0, 200.0, -200.0, 200.0, -5.0, 5.0);
}


int main(int argc, char ** argv) {
    BaseReader * reader = new FileReader();
    std::cout << "hi" << std::endl;
 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 200);
    glutCreateWindow("Our first GLUT application!");
    glutDisplayFunc(Display);
    Initialize();
    glutMainLoop();
    delete reader;
    return 0;
}