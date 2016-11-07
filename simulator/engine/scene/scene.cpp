#include "./scene.h"
#include "../shapes/base_shape.h"
#include <GL/glut.h>
#include "../camera/camera.h"


Scene::Scene():
    last_time(0),
    camera(new Camera()) {
    camera->setCrossVisible(false);
    AddShape(camera);
}

Scene::~Scene(){
    for(std::list<BaseShape *>::iterator iter = shapes.begin(), end=shapes.end();
        iter != end; iter++){
        delete (*iter);
    }
}


void Scene::UpdateAR(int w, int h){
    double ar=w/double(h);
    double c_ar=camera->width/camera->height;

    //маштабируем w
    if (ar > c_ar){
        int new_w = c_ar * h;
        int x = (w - new_w) >> 1;
        glViewport(x, 0, new_w, h);
    //маштабируем h
    }else {
        int new_h = w / c_ar;
        int y = (h - new_h) >> 1;
        glViewport(0, y, w, new_h);
    }
}

void Scene::updateDT(){
    int cur_time = glutGet(GLUT_ELAPSED_TIME);
    dt = (cur_time - last_time)/1000.;
    last_time = cur_time;
}

void Scene::Update(){
    updateDT();
    UpdateAR(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glClear(GL_COLOR_BUFFER_BIT); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(
        -camera->width/2.0, camera->width/2.0,
        -camera->height/2.0, camera->height/2.0);
    glTranslated(-camera->pos.x0, -camera->pos.x1, 0.0);
    glRotated(-camera->angle / M_PI * 180.0, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for(std::list<BaseShape *>::iterator iter = shapes.begin(), end=shapes.end();
        iter != end; iter++){
        (*iter)->Update();
    }
    glutSwapBuffers();
}

bool Scene::AddShape(BaseShape * shape){
    std::map<BaseShape *, std::list<BaseShape *>::iterator>::iterator iter =
        shapes_map.find(shape);

    // check shape reqursive
    if (iter != shapes_map.end()) {
        return false;
    }
    for(std::list<BaseShape *>::iterator iter = shapes.begin(), end=shapes.end();
        iter != end; iter++){
        if ((*iter)->HasShape(shape)){
            return false;
        }
    }

    std::list<BaseShape *>::iterator shape_iter = shapes.insert(shapes.end(), shape);
    shapes_map.insert(
        std::map<BaseShape *, std::list<BaseShape *>::iterator>::value_type(
            shape, shape_iter));
    return false;
}

bool Scene::RemoveShape(BaseShape * shape){
    std::map<BaseShape *, std::list<BaseShape *>::iterator>::iterator iter =
        shapes_map.find(shape);

    if (iter == shapes_map.end()){
        return false;
    }
    shapes.erase(iter->second);
    shapes_map.erase(iter);
    return true;
}