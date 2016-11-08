#ifndef __SIM_TRACTOR_MODEL__
#define __SIM_TRACTOR_MODEL__
#include "../base_tractor_model.h"
#include "../../common/thread/thread.h"

const double MAX_SPEED = 10.0;
const double MIN_SPEED = -10.0;
const double WHEEL_ANGLE_LIMMIT = 30. / 180. * M_PI;



class SimulateTractorModel:public BaseTractorModel, protected Thread{
public:
    SimulateTractorModel();
    virtual bool start();
    virtual bool stop();
    virtual TractorModelData get_data() const;
    void set_speed(double speed);
    double get_speed() const {return speed;}
    void set_wheel_angle(double angle);
    double get_wheel_angle() const {return wheel_angle;}

protected:
    SVec pos;
    double speed;
    double angle;
    double wheel_angle;
    double length;
    double dt;
    double time;

    Mutex mutex;
    bool stop_flag;
    TractorModelData data;
    void run();
    void update_data(double dt);
};

#endif // __BOX__