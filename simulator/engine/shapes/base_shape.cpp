#include "base_shape.h"
#include <GL/glut.h>

BaseShape::BaseShape():angle(0.){

};

BaseShape::~BaseShape(){
    for (std::list<BaseShape *>::iterator iter=childs.begin(), end=childs.end();
        iter != end; iter++) {
        delete *iter;
    }
}

bool BaseShape::HasShape(BaseShape * child, bool reqursive){
    if (!child){
        return false;
    }
    if (child_map.find(child) != child_map.end()){
        return true;
    }

    if (reqursive) {
        for (std::list<BaseShape *>::iterator iter=childs.begin(), end=childs.end();
            iter != end; iter++){
            if ((*iter)->HasShape(child)){
                return true;
            }
        }
    }
    return false;
} 


bool BaseShape::AddChild(BaseShape * child) {
    if (HasShape(child)){
        return false;
    }

    std::list<BaseShape *>::iterator iter = childs.insert(childs.end(), child);
    child_map.insert(
        std::map<BaseShape *, std::list<BaseShape *>::iterator>::value_type(
            child, iter));
    return true;
}


bool BaseShape::RemoveChild(BaseShape * child){
    if (!HasShape(child)){
        return true;
    }
    std::map<BaseShape *, std::list<BaseShape *>::iterator>::iterator iter =
        child_map.find(child);
    if (iter == child_map.end()){
         return false;
    }
    childs.erase(iter->second);
    child_map.erase(iter);
    return true;
}

void BaseShape::Update(){
    if (reshape){
        Reshape();
        reshape=false;
    }
    Draw();
    glPushMatrix();
    glRotated(angle, 0.0f, 0.0f, 1.0f);
    glTranslated(pos.x0, pos.x1, pos.x1);
    Draw();
    glPopMatrix();
}
