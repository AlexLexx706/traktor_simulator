#include "real_data_tractor_model.h"

RealDataTractorModel::RealDataTractorModel(BaseReader & _reader):
    reader(_reader),
    cur_sample(_reader.get_data().begin()),
    next_sample(_reader.get_data().begin())
{
}

bool RealDataTractorModel::start() {
    if (Thread::is_active() || reader.get_data().empty())
        return false;

    cur_sample = reader.get_data().begin();
    next_sample = cur_sample; next_sample++;
    return true;
}

bool RealDataTractorModel::stop(){
    return true;
}

void RealDataTractorModel::get_data(Data & out_date) const{

}

void RealDataTractorModel::run(){
    while(next_sample != reader.get_data().end()){
        sleep((next_sample->time - cur_sample->time) * 1000);
        cur_sample = next_sample;
        next_sample++;
    }
}
void RealDataTractorModel::update_data(){
    Mutex::ContextHelper ch(mutex);
    if (reader.get_data().empty()){
        return;
    }

    // //последний кадр
    // if (next_sample != reader.get_data().end()){
    //     const BaseReader::Data & first(*reader.get_data().begin());
    //     const BaseReader::Data & cur(*cur_sample);
    //     data.time = first.time - cur.time;
    //     data.wheel_angle = 0.0;
    //     data.angle = 
    // } else {

    // }
    // const BaseReader::Data & first(*reader.get_data().begin());
    // const BaseReader::Data & cur(*cur_sample);

}