#ifndef __TRACTOR__
#define __TRACTOR__
#include "../shapes/base_shape.h"

class Box;

class Tractor: public BaseShape {
public:
    Tractor();
    void setLenght(double length);
    void setWidth(double width);
    void setWheelsAngle(double angle);
private:
    Box * body;
    Box * back_left_wheel;
    Box * back_right_wheel;
    Box * front_left_wheel;
    Box * front_right_wheel;
    Box * tower;
    double width;
    double length;
    double wheel_angle;
    void rebuild();
};

#endif // __BOX__