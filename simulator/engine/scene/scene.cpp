#include "scene.h"

Scene::Scene() {

}

Scene::~Scene(){

}

void Scene::Update(){

}

bool Scene::AddShape(BaseShape * shape){
    std::map<BaseShape *, std::list<BaseShape *>::iterator>::iterator iter =
        shapes.find(shape);

    // check shape reqursive
    if (shape != shapes.end()) {
        for(std::list<BaseShape *>::iterator iter = shapes.begin(), end=shapes.end();
            iter != end; iter++){
            
        }
    }
}

bool Scene::RemoveShape(BaseShape * shape){

}
