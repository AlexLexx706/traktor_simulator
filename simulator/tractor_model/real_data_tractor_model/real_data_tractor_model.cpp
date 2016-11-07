#include "real_data_tractor_model.h"

RealDataTractorModel::RealDataTractorModel(BaseReader * reader){

}

bool RealDataTractorModel::start() {
    return true;
}
bool RealDataTractorModel::stop(){
    return true;
}

SVec RealDataTractorModel::get_pos() const {
    return SVec();
}

double RealDataTractorModel::get_speed() const {
    return 0.0;
}

SVec RealDataTractorModel::get_angle() const {
    return SVec();
}

double RealDataTractorModel::get_wheel_angle() const {
    return 0.0;
}

unsigned int RealDataTractorModel::get_time() const {
    return 0;
}
