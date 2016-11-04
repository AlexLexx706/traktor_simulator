#ifndef __BOX__
#define __BOX__
#include "../base_shape.h"
#include "../../../common/types.h"
#include <GL/glut.h>

class Box: public BaseShape {
public:
    Box();
    virtual ~Box(){};
    virtual void Update();
    void SetWidth(double width) {this->width=width; reshape=true;}
    double GetWidth() const {return width;}
    void SetHeight(double height) {this->height=height; reshape=true;}
    double GetHeight() const {return height;}
    void SetColor(const Color & color) {this->color=color; reshape=true;}
    const Color & GetColor() const {return color;}
protected:
    virtual void Reshape();
    virtual void Draw(); 

private:
    double width;
    double height;
    Color color;
    GLuint list_id;
};

#endif // __BOX__