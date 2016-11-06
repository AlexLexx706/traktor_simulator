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
    virtual void Update();
    bool AddShape(BaseShape * shape);
    bool RemoveShape(BaseShape * shape);
    double GetDt() const {return dt;};
    std::list<BaseShape *> & GetShapes(){return shapes;}
    Camera * getCamera() const {return camera;}
    
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


