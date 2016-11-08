#include "tractor.h"
#include "../shapes/box/box.h"
#include <iostream>
#include "../../tractor_model/base_tractor_model.h"

Tractor::Tractor():
    body(new Box()),
    back_left_wheel(new Box()),
    back_right_wheel(new Box()),
    front_left_wheel(new Box()),
    front_right_wheel(new Box()),
    tower(new Box()),
    width(2),
    length(4),
    wheel_angle(0.0)
{
    add_child(body);
    add_child(back_left_wheel);
    add_child(back_right_wheel);
    add_child(front_left_wheel);
    add_child(front_right_wheel);
    add_child(tower);
    rebuild();
}

void Tractor::rebuild(){
    std::cout << "base: " << static_cast<const BaseShape & >(*this) << std::endl;
    body->setWidth(width);
    body->setHeight(length);
    body->setColor(Color(1.0, 0.0, 0.0, 1.0));
    body->set_pos(SVec(0.0, length/2.0, 0.0));
    std::cout << "body: " << static_cast<const Box & >(*body) << std::endl;


    back_left_wheel->setWidth(width*0.25);
    back_left_wheel->setHeight(length*0.4);
    back_left_wheel->set_pos(SVec(-width/2.0, 0.0, 0.0));
    back_left_wheel->setColor(Color(0.0, 1.0, 0.0, 1.0));
    std::cout << "back_left_wheel: " << static_cast<const Box & >(*back_left_wheel) << std::endl;
    //std::cout << "w:" << back_left_wheel->getWidth() << " h:" << back_left_wheel->getHeight() << std::endl;

    back_right_wheel->setWidth(width*0.25);
    back_right_wheel->setHeight(length*0.4);
    back_right_wheel->set_pos(SVec(width/2.0, 0, 0.0));
    back_right_wheel->setColor(Color(0.0, 1.0, 0.0, 1.0));
    std::cout << "back_right_wheel: " << static_cast<const Box & >(*back_right_wheel) << std::endl;

    front_left_wheel->setWidth(width*0.2);
    front_left_wheel->setHeight(length*0.2);
    front_left_wheel->set_pos(SVec(-width/2.0, length, 0.0));
    front_left_wheel->setColor(Color(0.0, 0.0, 1.0, 1.0));

    std::cout << "front_left_wheel: " << static_cast<const Box & >(*front_left_wheel) << std::endl;

    front_right_wheel->setWidth(width*0.2);
    front_right_wheel->setHeight(length*0.2);
    front_right_wheel->set_pos(SVec(width/2.0, length, 0.0));
    front_right_wheel->setColor(Color(0.0, 0.0, 1.0, 1.0));
    std::cout << "front_right_wheel: " << static_cast<const Box & >(*front_right_wheel) << std::endl;

    tower->setWidth(width*0.7);
    tower->setHeight(length*0.5);
    tower->set_pos(SVec(0.0, tower->getHeight()/2.0, 0.0));
}

void Tractor::setLenght(double _length){
    if (_length!=length){
        length=_length;
        rebuild();
    }
}
void Tractor::setWidth(double _width){
    if (_width != width){
        width=_width;
        rebuild();
    }
}


void Tractor::setWheelsAngle(double angle){
    if (angle!=wheel_angle){
        wheel_angle=angle;
        front_left_wheel->get_angle(wheel_angle);
        front_right_wheel->get_angle(wheel_angle);
    }
}

void Tractor::update_data(const TractorModelData & data){
    set_pos(data.pos);
    get_angle(data.angle);
    setWheelsAngle(data.wheel_angle);
}