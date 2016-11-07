#include "real_data_tractor_model.h"

RealDataTractorModel::RealDataTractorModel(BaseReader & _reader):
    reader(_reader),cur_sample(reader.get_data().begin())   
{
}

bool RealDataTractorModel::start() {
    if (Thread::is_active())
        return false;
    cur_sample = reader.get_data().begin();   
    return true;
}

bool RealDataTractorModel::stop(){
    return true;
}

SVec RealDataTractorModel::get_pos() const {
    if (cur_sample.get_data().empty())
        return SVec(0, 0, 0);
    return cur_sample->ned_pos - reader.get_data().begin()->ned_pos;
}

double RealDataTractorModel::get_speed() const {
    if (cur_sample.get_data().empty())
        return 0;
    return cur_sample->speed;
}

double RealDataTractorModel::get_angle() const {
    return SVec();
}

double RealDataTractorModel::get_wheel_angle() const {
    return 0.0;
}

unsigned int RealDataTractorModel::get_time() const {
    if (cur_sample.get_data().empty())
        return 0;
    //время с нуля 
    return cur_sample->time - reader.get_data().begin()->time;
}

void RealDataTractorModel::run(){
    std::list<BaseReader::Data>::iterator next;
    while(cur_sample != reader.end()){
        next = cur_sample; next++;
    }
}   