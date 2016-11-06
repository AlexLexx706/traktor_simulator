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


Scene scene;
Box * box(new Box());
double step=0;
Tractor * tractor(new Tractor());

void Display() {
    scene.Update();
    for (std::list<BaseShape *>::iterator iter = scene.GetShapes().begin(), end=scene.GetShapes().end();
        iter != end; iter++) {
        (*iter)->setAngle((*iter)->getAngle() + step * scene.GetDt());
    }
}


int main(int argc, char ** argv) {
    //scene.AddShape(box);
    std::cout << "ned: " << ecef_to_ned(+2829169.83, +2208058.32, +5255180.65) << std::endl;
    FileReader reader;
    reader.open("tasks/sample.dat", 3);
    

    scene.AddShape(tractor);
    //scene.getCamera()->setY(10);
    //scene.getCamera()->setAngle(0.5);
    scene.getCamera()->setSize(10,10);
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