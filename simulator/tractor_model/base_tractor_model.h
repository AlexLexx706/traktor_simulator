#ifndef __BASE_TRACTOR_MODEL__
#define __BASE_TRACTOR_MODEL__
#include "../common/SMat.h"

//Используеться для обмена данными с движком отображения
struct TractorModelData{
    // позиция трактора в координатах модели
    SVec pos;
    
    // угол поворота колёс трактора рад.
    double wheel_angle;

    // ориентация модели трактора в рад. 0- направлен по оси y.
    double angle;

    //скорость трактора
    double speed;

    //time in ms
    unsigned int time;
    TractorModelData():wheel_angle(0.0),angle(0.0), speed(0.0), time(0){}
};


// интерфейс модели трактора с поворачивающимися передними колёсами
class BaseTractorModel{
public:
    virtual bool start() = 0;
    virtual bool stop() = 0;
    virtual TractorModelData get_data() const = 0;
};

inline std::ostream &operator<<(std::ostream &os, TractorModelData const &m) { 
    return os << "pos:" << m.pos << " wheel_angle:" << m.wheel_angle
        << " angle:" << m.angle << " speed:" << m.speed << " time:" << m.time; 
}


#endif // __BOX__