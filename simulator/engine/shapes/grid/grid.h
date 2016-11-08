#ifndef __GRID__
#define __GRID__
#include "../base_shape.h"
#include "../../../common/types.h"
#include <GL/glut.h>
#include <iostream>

class Grid: public BaseShape {
public:
    Grid();
    virtual ~Grid();
    void set_width(double _width){width=_width; reshape=true;}
    double get_width() const {return width;}
    void set_height(double _height){height=_height;}
    double get_height() const {return height;}
    void setColor(const Color & _color) {color=color;}
    const Color & getColor() const {return color;}
    void set_width_step(int step){width_step=step; reshape=true;}
    int get_width_step()const {return width_step;}
    void set_height_step(int step){height_step=step;}
    int get_height_step() const {return height_step;}    
protected:
    virtual void Reshape();
    virtual void Draw(); 
private:
    double width;
    double height;
    Color color;
    GLuint list_id;
    int width_step;
    int height_step;
};

inline std::ostream &operator<<(std::ostream &os, Grid const &m) { 
    return os << static_cast<const BaseShape &>(m)
        << " width:" << m.get_width() << " height:" << m.get_height()
        << " width_step:" << m.get_width_step()
        << " height_step:" << m.get_height_step()
        << " Color:" << m.getColor();
}


#endif // __BOX__