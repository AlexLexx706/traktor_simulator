#ifndef __SCENE__
#define __SCENE__
#include <list>
#include <map>

class Camera;
class BaseShape;

class Scene{
public:
    Scene();
    ~Scene();
    virtual void update();
    bool add_shape(BaseShape * shape);
    bool remove_shape(BaseShape * shape);
    double get_dt() const {return dt;};
    std::list<BaseShape *> & get_shapes(){return shapes;}
    Camera * get_camera() const {return camera;}
    
protected:
    std::list<BaseShape *> shapes;
    std::map<BaseShape *, std::list<BaseShape *>::iterator> shapes_map;
    
    int last_time;
    double dt;
    Camera * camera;
    
    void UpdateAR(int w, int h);
    void updateDT();
};
#endif // __BASE_ITEM__


