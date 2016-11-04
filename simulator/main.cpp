#include <GL/glut.h>
#include "reader/base_reader.h"
#include "reader/file_reader/file_reader.h"
#include "common/SMat.h"
#include "engine/scene/scene.h"
#include <iostream>

const int WIDTH=400;
const int HEIGHT=400;
Scene scene;

void Display() {
    glClear(GL_COLOR_BUFFER_BIT); 
    scene.Update();
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
    return 0;
}