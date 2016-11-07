#include "real_data_tractor_model.h"

RealDataTractorModel::RealDataTractorModel(BaseReader & _reader):
    reader(_reader),cur_sample(_reader.get_data().begin())   
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
void RealDataTractorModel::get_data(Data & out_date) const{

}

void RealDataTractorModel::run(){
    std::list<BaseReader::Data>::const_iterator next;
    while(cur_sample != reader.get_data().end()){
        next = cur_sample; next++;
    }
}   