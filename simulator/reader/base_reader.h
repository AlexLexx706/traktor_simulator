#ifndef __BASE_READER__
#define __BASE_READER__
#include "../common/SMat.h"
#include <list>
#include <iostream>

class BaseReader{
public:
    struct Data
    {
        //миллисекунды
        unsigned int time;

        // позиция в метрах x,y,z
        SVec ecef_pos;

        //скорость м/сек.
        double speed;

        //хз что это
        double azimut;

        // позиция широта(рад.), долгота(рад.), высота(над уровнием моря, метры)
        SVec ned_pos;
    };

    BaseReader(){};

    virtual ~BaseReader(){};

    //Возвращает данные 
    virtual const std::list<BaseReader::Data> & get_gata() const = 0;
};

inline std::ostream &operator<<(std::ostream &os, BaseReader::Data const &m) { 
    return os << "time:" << m.time << " ecef_pos:" << m.ecef_pos << " speed:" << m.speed << " azomit:" << m.azimut << " ned_pos:" << m.ned_pos; 
}



#endif