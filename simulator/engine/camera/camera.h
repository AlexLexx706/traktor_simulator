#ifndef __CAMERA__
#define __CAMERA__
#include "../shapes/base_shape.h"

class Scene;
class Camera: public BaseShape {
public:
    Camera();
    void setSize(double width, double height);
    void set_scale(double _scale) {scale=_scale;}
private:
    double width;
    double height;
    double scale;
    friend Scene;
};

#endif // __BOX__