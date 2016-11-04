#include "./scene.h"
#include "../shapes/base_shape.h"
#include <GL/glut.h>

Scene::Scene() {

}

Scene::~Scene(){
    for(std::list<BaseShape *>::iterator iter = shapes.begin(), end=shapes.end();
        iter != end; iter++){
        delete (*iter);
    }
}

void Scene::Update(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for(std::list<BaseShape *>::iterator iter = shapes.begin(), end=shapes.end();
        iter != end; iter++){
        (*iter)->Update();
    }
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
