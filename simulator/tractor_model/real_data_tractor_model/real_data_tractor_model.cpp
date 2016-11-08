#include "real_data_tractor_model.h"
#include <iostream>
#include "../../common/coordinat_converter/coordinat_converter.h"
#include "../../common/trace.h"

RealDataTractorModel::RealDataTractorModel(BaseReader & _reader):
    reader(_reader),
    cur_sample(_reader.get_data().begin()),
    next_sample(_reader.get_data().begin()),
    stop_flag(true)
{
}

bool RealDataTractorModel::start() {
    //BlockTrace bt("RealDataTractorModel::start");

    if (!stop_flag) {
        std::cerr << "thread is active" << std::endl;
    }

    if (reader.get_data().empty()){
        std::cerr << "data empty" << std::endl;
        return false;
    }

    cur_sample = reader.get_data().begin();
    next_sample = cur_sample;
    next_sample++;
    stop_flag=false;
    
    data.pos = SVec();
    data.wheel_angle = 0.0;
    data.angle = 0.0;
    data.speed = 0;
    data.time = 0;
    Thread::start();
    return true;
}

bool RealDataTractorModel::stop(){
    //BlockTrace bt("RealDataTractorModel::stop");
    if (stop_flag) {
        std::cerr << "thread is not active" << std::endl;
        return false;
    }
    stop_flag=true;
    Thread::join();
    return true;
}

TractorModelData RealDataTractorModel::get_data() const{
    Mutex::ContextHelper ch(const_cast<Mutex &>(mutex));
    TractorModelData out_date(data);
    return out_date;
}

void RealDataTractorModel::run(){
    //BlockTrace bt("RealDataTractorModel::run");
    while(!stop_flag && next_sample != reader.get_data().end()){
        sleep((next_sample->time - cur_sample->time) * 1000);
        cur_sample = next_sample;
        next_sample++;
        update_data();
    }
}

void RealDataTractorModel::update_data(){
    //BlockTrace bt("RealDataTractorModel::update_data");
    Mutex::ContextHelper ch(mutex);
    if (reader.get_data().empty()){
        return;
    }

    //последний кадр
    if (next_sample == reader.get_data().end()){
        const BaseReader::Data & first(*reader.get_data().begin());
        const BaseReader::Data & cur(*cur_sample);
        data.pos = (cur.ned_pos - first.ned_pos) * EARTH_RADIUS;
        data.wheel_angle = 0.0;
        data.angle = data.angle;
        data.speed = cur.speed;
        data.time = cur.time - first.time;
    } else {
        const BaseReader::Data & first(*reader.get_data().begin());
        const BaseReader::Data & cur(*cur_sample);
        const BaseReader::Data & next(*next_sample);

        data.pos = (cur.ned_pos - first.ned_pos) * EARTH_RADIUS;
        data.wheel_angle = 0.0;
        SVec dir(next.ned_pos - cur.ned_pos);
        double dir_len(dir.length());
        if (dir_len){
            dir /= dir_len;
            data.angle = dir_len != 0.0 ? acos(dir.x1/1.0) * (-dir.x0 > 0 ? 1.0 : -1.0) : 0.0;           
        }
        data.speed = cur.speed;
        data.time = cur.time - first.time;
    }
    std::cout << "update_data: " << data << std::endl;
}