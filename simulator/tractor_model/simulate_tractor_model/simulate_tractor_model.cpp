#include "simulate_tractor_model.h"
#include "../../common/trace.h"

SimulateTractorModel::SimulateTractorModel():
    speed(0.0),
    angle(0.0),
    wheel_angle(0.0),
    length(4.0),
    dt(1.0 / 25.0),
    time(0.0),
    stop_flag(true)
{

}

bool SimulateTractorModel::start(){
    BlockTrace bt("SimulateTractorModel::start");
    
    if (!stop_flag) {
        std::cerr << "thread is active" << std::endl;
    }
    stop_flag=false;
    Thread::start();
    return true;
}

bool SimulateTractorModel::stop(){
    BlockTrace bt("SimulateTractorModel::stop");

    if (stop_flag) {
        std::cerr << "thread is not active" << std::endl;
        return false;
    }
    stop_flag=true;
    Thread::join();
    return true;
}

TractorModelData SimulateTractorModel::get_data() const{
    Mutex::ContextHelper ch(const_cast<Mutex &>(mutex));
    TractorModelData out(data);
    return out;
}

void SimulateTractorModel::run(){
    BlockTrace bt("SimulateTractorModel::run");

    unsigned int cur_dt(dt*1000000);
    while (!stop_flag){
        sleep(cur_dt);
        time += dt;
        update_data(dt);
    }
}

void SimulateTractorModel::update_data(double dt){
    //BlockTrace bt("SimulateTractorModel::update_data");

    angle += ((tan(wheel_angle) / length) * speed) * dt;
    pos.x0 += (cos(angle + M_PI_2) * speed) * dt;
    pos.x1 += (sin(angle + M_PI_2) * speed) * dt;

    Mutex::ContextHelper ch(mutex);
    data.pos = pos;
    data.time = time * 1000.0;
    data.angle = angle;
    data.wheel_angle = wheel_angle;
    data.speed = speed;
}   

void SimulateTractorModel::set_speed(double _speed){
    _speed = _speed > MAX_SPEED ? MAX_SPEED: _speed;
    _speed = _speed < MIN_SPEED ? MIN_SPEED: _speed;
    speed = _speed;
}

void SimulateTractorModel::set_wheel_angle(double angle){
    angle = angle > WHEEL_ANGLE_LIMMIT ? WHEEL_ANGLE_LIMMIT : angle;
    angle = angle < -WHEEL_ANGLE_LIMMIT ? -WHEEL_ANGLE_LIMMIT : angle;
    wheel_angle = angle;
}
