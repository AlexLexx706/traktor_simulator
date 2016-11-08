#ifndef __SIM_TRACTOR_MODEL__
#define __SIM_TRACTOR_MODEL__
#include "../base_tractor_model.h"
#include "../../common/thread/thread.h"

class SimulateTractorModel:public BaseTractorModel, protected Thread{
public:
    SimulateTractorModel();
    virtual bool start();
    virtual bool stop();
    virtual void get_data(Data & out_date) const;

protected:
    Mutex mutex;
    bool stop_flag;
    void run();
    void update_data();
};

#endif // __BOX__