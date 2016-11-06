#ifndef __CAMERA__
#define __CAMERA__
#include "../shapes/base_shape.h"

class Scene;
class Camera: public BaseShape {
public:
    Camera();
    void setSize(double width, double height);
private:
    double width;
    double height;
    friend Scene;
};

#endif // __BOX__