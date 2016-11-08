#include <GL/glut.h>
#include "reader/base_reader.h"
#include "reader/file_reader/file_reader.h"
#include "common/SMat.h"
#include "engine/scene/scene.h"
#include "engine/shapes/box/box.h"
#include "engine/tractor/tractor.h"
#include "engine/camera/camera.h"
#include <iostream>
#include "common/coordinat_converter/coordinat_converter.h"
#include "common/thread/thread.h"
#include "tractor_model/real_data_tractor_model/real_data_tractor_model.h"
#include "tractor_model/simulate_tractor_model/simulate_tractor_model.h"

Scene scene;
Box * box(new Box());
double step=0;
Tractor * tractor(new Tractor());
BaseTractorModel * model(NULL);
BaseTractorModel::Data model_data;

void Display() {
    scene.Update();
    // for (std::list<BaseShape *>::iterator iter = scene.GetShapes().begin(), end=scene.GetShapes().end();
    //     iter != end; iter++) {
    //     (*iter)->setAngle((*iter)->getAngle() + step * scene.GetDt());
    // }
    model->get_data(model_data);
    tractor->setPos(model_data.pos);
    tractor->setAngle(model_data.angle);
    tractor->setWheelsAngle(model_data.wheel_angle);

}

class TestThread:public Thread{
public:
    void run(){
        while(1){
            sleep(1000000);
            std::cout << get_value() << std::endl;
        }
    }
    void set_value(int _value){
        Mutex::ContextHelper mh(mutex);
        sleep(5000000);
        value=_value;
    };
    
    int get_value() const {
        Mutex::ContextHelper mh(const_cast<Mutex &>(mutex));
        return value;
    }

private:
    int value;
    Mutex mutex;
};

int main(int argc, char ** argv) {
    //FileReader reader;
    //reader.open("./tasks/sample.dat");
    //model = new RealDataTractorModel(reader);
    model = new SimulateTractorModel();
    static_cast<SimulateTractorModel *>(model)->set_speed(1);
    static_cast<SimulateTractorModel *>(model)->set_wheel_angle(0.5);
    model->start();
    // Thread::sleep(100000);
    // model.start();
    // model.stop();
    // model.start();

    scene.AddShape(tractor);
    //scene.getCamera()->setY(10);
    //scene.getCamera()->setAngle(0.5);
    scene.getCamera()->setSize(50,50);
    scene.getCamera()->setPos(SVec(0, 0, 0));
    tractor->setWheelsAngle(1);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glDisable(GL_DEPTH_TEST);
    glutInitWindowSize(100, 100);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Tractor simulator");
    glutDisplayFunc(Display);
    glutIdleFunc(Display);
    glutMainLoop();
    return 0;
}