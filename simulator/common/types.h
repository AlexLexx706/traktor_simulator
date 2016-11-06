#ifndef __COMMON_TYPES__
#define __COMMON_TYPES__

struct Color{
    double r,g,b,a;
    Color(double _r=1.0, double _g=1.0, double _b=1.0, double _a=1.0):
        r(_r), g(_g), b(_b), a(_a){}
};

#endif // __BOX__