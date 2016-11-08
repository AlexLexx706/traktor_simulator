#include "simulate_tractor_model.h"

SimulateTractorModel::SimulateTractorModel():
    speed(0.0),
    Q(0.0),
    V_Q(0.0),
    wheel_angle(0.0),
    length(4.0),
    dt(1.0 / 25.0),
    time(0.0),
    stop_flag(true)
{

}

bool SimulateTractorModel::stop(){
   if (!stop_flag) {
        std::cerr << "thread is active" << std::endl;
    }

    Thread::start();
    return true;
}

bool SimulateTractorModel::start(){
    if (stop_flag) {
        std::cerr << "thread is not active" << std::endl;
        return false;
    }
    stop_flag=true;
    Thread::join();
    return true;
}

void SimulateTractorModel::get_data(Data & out_date) const{
    Mutex::ContextHelper ch(const_cast<Mutex &>(mutex));
    out_date = data;
}

void SimulateTractorModel::run(){
    unsigned int cur_dt(dt*1000000);

    while (!stop_flag){
        sleep(cur_dt);
        time += dt;
        update_data(dt);
    }
}

void SimulateTractorModel::update_data(double dt){
    Q += ((tan(wheel_angle) / length) * speed) * dt;
    pos.x0 += (cos(Q + M_PI_2) * speed) * dt;
    pos.x1 += (sin(Q + M_PI_2) * speed) * dt;

    Mutex::ContextHelper ch(mutex);
    data.pos = pos;
    data.time = time * 1000.0;
    data.angle = Q;
    data.wheel_angle = wheel_angle;
    data.speed = speed;
}
