#include "./scene.h"
#include "../shapes/base_shape.h"
#include <GL/glut.h>
#include "../camera/camera.h"

Scene::Scene():
    last_time(0),
    camera(new Camera()) {
    camera->set_cross_visible(false);
    add_shape(camera);
}

Scene::~Scene(){
    for(std::list<BaseShape *>::iterator iter = shapes.begin(), end=shapes.end();
        iter != end; iter++){
        delete (*iter);
    }
    for (std::list<Text *>::iterator iter = texts.begin(), end = texts.end();
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


void Scene::update(){
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
    glScaled(camera->scale, camera->scale, camera->scale);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    for(std::list<BaseShape *>::iterator iter = shapes.begin(), end=shapes.end();
        iter != end; iter++){
        (*iter)->update();
    }

    glMatrixMode (GL_PROJECTION); // use PROJECTION matrix
    glLoadIdentity();
    gluOrtho2D(0, 1.0, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //out_string_at(GLUT_BITMAP_TIMES_ROMAN_24, 14, 5, "Hello World");
    for (std::list<Text *>::iterator iter = texts.begin(), end = texts.end();
            iter != end; iter++){

        glColor4d(
            (*iter)->color.r, (*iter)->color.g,
            (*iter)->color.b, (*iter)->color.a);
        draw_text(
            (*iter)->font, (*iter)->pos.x0, (*iter)->pos.x1, (*iter)->str);
    }
    glutSwapBuffers();
}

bool Scene::add_shape(BaseShape * shape){
    std::map<BaseShape *, std::list<BaseShape *>::iterator>::iterator iter =
        shapes_map.find(shape);

    // check shape reqursive
    if (iter != shapes_map.end()) {
        return false;
    }
    for(std::list<BaseShape *>::iterator iter = shapes.begin(), end=shapes.end();
        iter != end; iter++){
        if ((*iter)->has_shape(shape)){
            return false;
        }
    }

    std::list<BaseShape *>::iterator shape_iter = shapes.insert(shapes.end(), shape);
    shapes_map.insert(
        std::map<BaseShape *, std::list<BaseShape *>::iterator>::value_type(
            shape, shape_iter));
    return false;
}

bool Scene::remove_shape(BaseShape * shape){
    std::map<BaseShape *, std::list<BaseShape *>::iterator>::iterator iter =
        shapes_map.find(shape);

    if (iter == shapes_map.end()){
        return false;
    }
    shapes.erase(iter->second);
    shapes_map.erase(iter);
    return true;
}

void Scene::draw_text(void *font, double x, double y, const std::string & str)
{
    font = font ? font: GLUT_BITMAP_8_BY_13;
    glRasterPos2d(x, y); // set position
    
    for (std::string::const_iterator iter=str.begin(), end=str.end();
            iter !=end; iter++){
        glutBitmapCharacter(font, *iter);
    }
}

bool Scene::add_text(Text * text){
    if (!text){
        std::cerr << "text == NULL" << std::endl;
        return false;
    }
    std::map<Text *, std::list<Text *>::iterator>::iterator iter = texts_map.find(text);

    if (iter != texts_map.end()){
        std::cerr << "text already in scene" << std::endl;
        return false;
    }
    texts_map.insert(
        std::map<Text *, std::list<Text *>::iterator>::value_type(
            text, texts.insert(texts.end(), text)));
    return true;
}

bool Scene::remove_text(Text * text){
    if (!text){
        std::cerr << "text == NULL" << std::endl;
        return false;
    }
    std::map<Text *, std::list<Text *>::iterator>::iterator iter = texts_map.find(text);

    if (iter == texts_map.end()){
        std::cerr << "text not exist in scene" << std::endl;
        return false;
    }
    texts.erase(iter->second);
    texts_map.erase(iter);
    return true;
}
