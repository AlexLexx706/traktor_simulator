#ifndef __BASE_ITEM__
#define __BASE_ITEM__
#include <list>
#include <map>
#include "../../common/SMat.h"

class BaseShape;

class BaseShape{
public:
    BaseShape();
    virtual ~BaseShape();
    virtual void Update();
    bool HasShape(BaseShape * child, bool reqursive=false); 
    bool AddChild(BaseShape * child);
    bool RemoveChild(BaseShape * child);
    const std::list<BaseShape*> & GetChilds(){return childs;};
    const SVec & GetPos() const {return pos;};
    double GetAngle() const {return angle;}

protected:
    virtual void Reshape(){};
    virtual void Draw(){};

    bool reshape;
    std::list<BaseShape *> childs;
    std::map<BaseShape *, std::list<BaseShape *>::iterator> child_map;
    SVec pos;
    double angle;
};
#endif // __BASE_ITEM__