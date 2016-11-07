#ifndef __BASE_TRACTOR_MODEL__
#define __BASE_TRACTOR_MODEL__
#include "../common/SMat.h"

// интерфейс модели трактора с поворачивающимися передними колёсами
class BaseTractorModel{
public:
    //Используеться для обмена данными с движком отображения
    struct Data{
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
        Data():wheel_angle(0.0),angle(0.0), speed(0.0), time(0){}
    };

    virtual bool start() = 0;
    virtual bool stop() = 0;
    virtual void get_data(Data & out_date) const = 0;
};

#endif // __BOX__