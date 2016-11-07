#ifndef __REAL_TRACTOR_MODEL__
#define __REAL_TRACTOR_MODEL__
#include "../base_tractor_model.h"
#include "../../common/thread/thread.h"
#include "../../reader/base_reader.h"

class BaseReader;

class RealDataTractorModel:public BaseTractorModel, protected Thread{
public:
    RealDataTractorModel(BaseReader & reader);
    virtual bool start();
    virtual bool stop();
    virtual void get_data(Data & out_date) const;
protected:
    BaseReader & reader;
    std::list<BaseReader::Data>::const_iterator cur_sample;
    BaseTractorModel::Data data;
    void run();
};

#endif // __BOX__