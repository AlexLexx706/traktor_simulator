#ifndef __BASE_ITEM__
#define __BASE_ITEM__
#include <list>
#include <map>

class BaseItem;

class BaseItem{
public:
    BaseItem();
    virtual ~BaseItem();
    virtual void Draw() = 0;
    virtual void Update();
    bool AddChild(BaseItem * child);
    bool RemoveChild(BaseItem * child);
    const std::list<BaseItem> & GetChilds() const;
private:
    std::list<BaseItem *> childs;
    std::map<BaseItem *, std::list<BaseItem *>::iterator> child_map; 
};
#endif // __BASE_ITEM__