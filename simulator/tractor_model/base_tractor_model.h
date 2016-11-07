#ifndef __BASE_TRACTOR_MODEL__
#define __BASE_TRACTOR_MODEL__
#include "../common/SMat.h"

// интерфейс модели трактора с поворачивающимися передними колёсами
class BaseTractorModel{
public:
    //Используеться для обмена данными с движком отображения
    class Data{
        // позиция трактора в координатах модели
        SVec pos;
        
        // угол поворота колёс трактора рад.
        double wheel_angle;

        // ориентация модели трактора в рад. 0- направлен по оси y.
        double angle;
    };

    virtual bool start() = 0;

    virtual bool stop() = 0;

    virtual SVec get_pos() const = 0;

    virtual double get_speed() const = 0;

    virtual unsigned int get_time() const = 0;

    virtual SVec get_angle() const = 0;

    virtual double get_wheel_angle() const = 0;
};

#endif // __BOX__