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
    virtual void update();
    bool has_shape(BaseShape * child, bool reqursive=false); 
    bool add_child(BaseShape * child);
    bool remove_child(BaseShape * child);
    const std::list<BaseShape*> & get_childs(){return childs;};

    void set_pos(const SVec & _pos){pos=_pos;}
    const SVec & get_pos() const {return pos;};

    void get_angle(double _angle) {angle=_angle;}
    double getAngle() const {return angle;}
    void set_x(double x){pos.x0=x;}
    void set_y(double y){pos.x1=y;}
    double get_x() const {return pos.x0;}
    double get_y() const {return pos.x1;}
    void set_cross_visible(bool visible){show_cross=visible;}
    bool is_cross_visible() const {return show_cross;}

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
    return os << "pos: " << m.get_pos() << " angle:" << m.getAngle();
}

#endif // __BASE_ITEM__