#include "camera.h"

Camera::Camera():
    width(10.0),
    height(10.0),
    scale(1.0){

}

void Camera::setSize(double _width, double _height){
    width=_width;
    height=_height;
}
