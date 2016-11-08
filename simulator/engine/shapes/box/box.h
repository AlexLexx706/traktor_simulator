#ifndef __BOX__
#define __BOX__
#include "../base_shape.h"
#include "../../../common/types.h"
#include <GL/glut.h>
#include <iostream>

class Box: public BaseShape {
public:
    Box();
    virtual ~Box();
    void setWidth(double width) {this->width=width; reshape=true;}
    double getWidth() const {return width;}
    void setHeight(double height) {this->height=height; reshape=true;}
    double getHeight() const {return height;}
    void setColor(const Color & color) {this->color=color; reshape=true;}
    const Color & getColor() const {return color;}
protected:
    virtual void Reshape();
    virtual void Draw(); 

private:
    double width;
    double height;
    Color color;
    GLuint list_id;
};

inline std::ostream &operator<<(std::ostream &os, Box const &m) { 
    return os << static_cast<const BaseShape &>(m) << " width:" << m.getWidth() << " height:" << m.getHeight() << " Color:" << m.getColor();
}


#endif // __BOX__