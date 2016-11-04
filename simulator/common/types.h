#ifndef __COMMON_TYPES__
#define __COMMON_TYPES__

struct Color{
    double r,g,b,a;
    Color():r(1.0),g(1.0),b(1.0),a(1.0){}
    Color(double _r, double _g,double _b, double _a):
        r(_r),g(_g),b(_b){}
};

#endif // __BOX__