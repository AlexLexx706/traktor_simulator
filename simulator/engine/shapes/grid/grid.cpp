#include "grid.h"

Grid::Grid():
    width(100.0),
    height(100.0),
    list_id(-1),
    width_step(100),
    height_step(100)
{
}
Grid::~Grid(){

}

void Grid::Reshape(){
    if (glIsList(list_id)){
        glDeleteLists(list_id, 1);
    }

    list_id = glGenLists(1);
    glNewList(list_id, GL_COMPILE);
    glBegin(GL_LINES);
    double start_x(-width / 2.0), step_x(width / width_step);
    double start_y(-height / 2.0), step_y(height / height_step);
    std::cout << "grid: " << *this << std::endl;

    for (int i = 0; i <= width_step; i++){
        glVertex2d(start_x + i * step_x, start_y);
        glVertex2d(start_x + i * step_x, -start_y);
    }

    for (int i = 0; i <= height_step; i++){
        glVertex2d(start_x, start_y + step_y * i);
        glVertex2d(-start_x, start_y + step_y * i);
    }
    glEnd(); 
    glEndList();
}

void Grid::Draw(){
    glColor4d(color.r, color.g, color.b, color.a);
    glCallList(list_id);
}