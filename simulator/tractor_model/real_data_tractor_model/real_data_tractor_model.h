#ifndef __REAL_TRACTOR_MODEL__
#define __REAL_TRACTOR_MODEL__
#include "../base_tractor_model.h"

class BaseReader;

class RealDataTractorModel:public BaseTractorModel{
public:
    RealDataTractorModel(BaseReader * reader);
    virtual bool start();
    virtual bool stop();
    SVec get_pos() const;
    double get_speed() const;
    SVec get_angle() const;
    double get_wheel_angle() const;
    unsigned int get_time() const;
};

#endif // __BOX__