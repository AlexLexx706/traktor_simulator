#include "box.h"
#include <GL/glut.h>

Box::Box():
    width(10.),
    height(10.),
    list_id(-1){
}

Box::~Box(){
}

void Box::Reshape(){
    if (glIsList(list_id)){
        glDeleteLists(list_id, 1);
    }

    list_id = glGenLists(1);
    glNewList(list_id, GL_COMPILE);
    glBegin(GL_QUADS);
    glColor4d(color.r, color.g, color.b, color.a);
    double w_2=width/2.0;
    double h_2=height/2.0;
    glVertex2d(-w_2, -h_2);
    glVertex2d(w_2, -h_2);
    glVertex2d(w_2, h_2);
    glVertex2d(-w_2, h_2);
    glEnd(); 
    glEndList();
} 

void Box::Draw(){
    glCallList(list_id);
}


