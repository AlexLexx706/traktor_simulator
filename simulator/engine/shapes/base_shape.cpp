#include "base_shape.h"
#include <GL/glut.h>

BaseShape::BaseShape():
    reshape(true), angle(0.),cross_len(1.0),show_cross(true){
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
    glPushMatrix();
    glTranslated(pos.x0, pos.x1, pos.x2);
    glRotated(angle / M_PI * 180.0, 0.0f, 0.0f, 1.0f);
    Draw();
    
    if (show_cross){
        drawCross();
    }

    for (std::list<BaseShape *>::iterator iter=childs.begin(), end=childs.end();
        iter != end; iter++) {
        (*iter)->Update();
    }
    glPopMatrix();
}

void BaseShape::drawCross(){
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(cross_len, 0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(0, cross_len);
    glEnd();
}