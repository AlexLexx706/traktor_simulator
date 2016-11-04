#include <GL/glut.h>
//#include <GL/glew.h>
#include "reader/base_reader.h"
#include "reader/file_reader/file_reader.h"
#include "common/SMat.h"
#include <iostream>

const int WIDTH=400;
const int HEIGHT=400;

SVec vectors[1];
GLuint VBO;

void Drow(){
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2i(250, 450);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2i(250, 150);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(550, 150);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(550, 450);
    glEnd(); 
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT); 
    Drow();
    glutSwapBuffers();
}

void Reshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc, char ** argv) {
    vectors[0] = SVec(0.0f, 0.0f, 0.0f);
    BaseReader * reader = new FileReader();
    std::cout << "hi" << std::endl;
 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 200);
    glutReshapeFunc(Reshape);
    glutCreateWindow("Tractor simulator");
    glutDisplayFunc(Display);
    Reshape(WIDTH, HEIGHT);
    glutMainLoop();
    delete reader;
    return 0;
}