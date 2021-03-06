#include <GL/glut.h>
#include "reader/base_reader.h"
#include "reader/file_reader/file_reader.h"
#include "common/SMat.h"
#include "engine/scene/scene.h"
#include "engine/shapes/box/box.h"
#include "engine/shapes/grid/grid.h"
#include "engine/tractor/tractor.h"
#include "engine/camera/camera.h"
#include <iostream>
#include "common/coordinat_converter/coordinat_converter.h"
#include "common/thread/thread.h"
#include "tractor_model/real_data_tractor_model/real_data_tractor_model.h"
#include "tractor_model/simulate_tractor_model/simulate_tractor_model.h"
#include <sstream>
#include <stdio.h>

Scene scene;
Tractor * tractor(new Tractor());
BaseTractorModel * model(NULL);
SimulateTractorModel* sim_model(NULL);
RealDataTractorModel* real_data_model(NULL);
Scene::Text * info_text(new Scene::Text("", SVec(0, 0.01, 0), GLUT_BITMAP_TIMES_ROMAN_24));


const double CAMERA_SCALE_STEP = 0.01;
const double CAMERA_MOVE_STEP = 0.05;
const double WHEEL_ANGLE_STEP = 0.05;
const double SPEED_STEP = 0.1;

bool move_camera(false);
int start_move_pos[2];

static int fps_counter = 0;
static int cur_fps = 0;
static long long fps_start_time = Thread::get_timestemp_ms();
static long long cur_time;


void Display() {
    cur_time = Thread::get_timestemp_ms();
    //fprintf(stderr, "cur_time:%lld s_t:%lld\n", cur_time, fps_start_time + 1000LL);

    if (cur_time  > (fps_start_time + 1000LL)) {
        //fprintf(stderr, "!!\n");
        cur_fps = fps_counter;
        fps_counter = 0;
        fps_start_time = cur_time;
    }
    fps_counter++;
    scene.update();
    TractorModelData data(model->get_data());
    tractor->update_data(data);
    std::stringstream ss;
    ss.setf(std::ios::fixed);\
    ss.precision(3);
    ss << "fps:" << cur_fps << " x:" << data.pos.x0 << " y:" << data.pos.x1 << "  angle:" << data.angle << "  w_angle:" << data.wheel_angle << "  speed:" << data.speed << "  time:" << data.time;
    info_text->set_text(ss.str());
}

void mouse_callback(int button, int state, int x, int y){
    //std::cout << "button: " << button << " state: " << state << " x:" << x << " y:" << y << std::endl;
    // масштабирование камеры
    switch (button){
        case 0:
            move_camera = !state;
            start_move_pos[0] = x; start_move_pos[1] = y;
            break;
        case 3:
            scene.get_camera()->set_scale(
                scene.get_camera()->get_scale() + CAMERA_SCALE_STEP);
            break;
        case 4:
            scene.get_camera()->set_scale(
                scene.get_camera()->get_scale() - CAMERA_SCALE_STEP);
            break;
    }
}

void motion_callback(int x, int y){
    if (move_camera){

        SVec offset(
            -(x - start_move_pos[0]) * CAMERA_MOVE_STEP,
            (y - start_move_pos[1]) * CAMERA_MOVE_STEP,
            0.0);
        Camera & camera(*scene.get_camera());
        camera.set_pos(camera.get_pos() + offset);
        //std::cout << "offset: " << offset << " camera_pos:" << camera.get_pos() << std::endl;
        start_move_pos[0] = x; start_move_pos[1] = y;
    }
}


void keyboard_callback(unsigned char key, int x, int y){
    //std::cout << "key: " << key << " x:" << x << " y:" << y << std::endl;
    switch (key){
        case 'w':
            sim_model->set_speed(sim_model->get_speed() + SPEED_STEP);
            model = sim_model;
            break;
        case 's':
            sim_model->set_speed(sim_model->get_speed() - SPEED_STEP);
            model = sim_model;
            break;
        case ' ':
            sim_model->set_speed(0.);
            sim_model->set_wheel_angle(0.0);
            model = sim_model;
            break;
        case 'a':
            sim_model->set_wheel_angle(sim_model->get_wheel_angle() + WHEEL_ANGLE_STEP);
            model = sim_model;
            break;
        case 'd':
            sim_model->set_wheel_angle(sim_model->get_wheel_angle() - WHEEL_ANGLE_STEP);
            model = sim_model;
            break;
        case 'e':
            model = real_data_model;
            real_data_model->start();
            break;
        case 'r':
            model = real_data_model;
            real_data_model->stop();
            break;
    }
}


int main(int argc, char ** argv) {
    std::cout << "argc:" << argc << " ars: ";
    for (int i=0; i < argc; i++){
        std::cout << argv[i] << ' ';
    }
    std::cout << std::endl;

    FileReader reader;
    reader.open(argc > 1 ? argv[1] : "./tasks/sample.dat");
    real_data_model = new RealDataTractorModel(reader);
    sim_model = new SimulateTractorModel();
    model = sim_model;
    model->start();
    Grid * grid(new Grid());
    grid->set_width(500);
    grid->set_height(500);
    grid->set_cross_length(50);
    scene.add_shape(grid);
    scene.add_shape(tractor);
    //scene.get_camera()->set_y(10);
    //scene.get_camera()->get_angle(0.5);
    scene.get_camera()->setSize(50,50);
    scene.get_camera()->set_pos(SVec(0, 0, 0));
    scene.add_text(info_text);
    tractor->setWheelsAngle(1);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel (GL_FLAT); // The default value is GL_SMOOTH
    glDisable(GL_DEPTH_TEST);
    glutInitWindowSize(100, 100);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Tractor simulator");
    glutKeyboardFunc(keyboard_callback);
    glutMouseFunc(mouse_callback);
    glutMotionFunc(motion_callback);
    glutDisplayFunc(Display);
    glutIdleFunc(Display);
    glutMainLoop();
    return 0;
}