#ifndef __SCENE__
#define __SCENE__
#include <list>
#include <map>

class BaseShape;

class Scene{
public:
    Scene();
    ~Scene();
    virtual void Update();
    bool AddShape(BaseShape * shape);
    bool RemoveShape(BaseShape * shape);

protected:
    std::list<BaseShape *> shapes;
    std::map<BaseShape *, std::list<BaseShape *>::iterator> child_map;
};
#endif // __BASE_ITEM__


