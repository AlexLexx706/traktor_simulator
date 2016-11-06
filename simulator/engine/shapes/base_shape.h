#ifndef __BASE_ITEM__
#define __BASE_ITEM__
#include <list>
#include <map>
#include "../../common/SMat.h"
#include <iostream>

class BaseShape;
class Scene;

class BaseShape{
public:
    BaseShape();
    virtual ~BaseShape();
    virtual void Update();
    bool HasShape(BaseShape * child, bool reqursive=false); 
    bool AddChild(BaseShape * child);
    bool RemoveChild(BaseShape * child);
    const std::list<BaseShape*> & GetChilds(){return childs;};

    void setPos(const SVec & pos){this->pos=pos;}
    const SVec & getPos() const {return pos;};

    void setAngle(double angle) {this->angle=angle;}
    double getAngle() const {return angle;}
    void setX(double x){pos.x0=x;}
    void setY(double y){pos.x1=y;}
    double getX() const {return pos.x0;}
    double getY() const {return pos.x1;}
    void setCrossVisible(bool visible){show_cross=visible;}
    bool isCrossVisible() const {return show_cross;}

protected:
    virtual void Reshape(){};
    virtual void Draw(){};
    void drawCross();

    bool reshape;
    std::list<BaseShape *> childs;
    std::map<BaseShape *, std::list<BaseShape *>::iterator> child_map;
    SVec pos;
    double angle;
    double cross_len;
    bool show_cross;
    friend Scene;
};

inline std::ostream &operator<<(std::ostream &os, BaseShape const &m) { 
    return os << "pos: " << m.getPos() << " angle:" << m.getAngle();
}

#endif // __BASE_ITEM__