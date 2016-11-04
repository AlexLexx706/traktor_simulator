#include "base_item.h"

BaseItem::BaseItem() {
}

BaseItem::~BaseItem() {
}

void BaseItem::Update() {
}


bool BaseItem::AddChild(BaseItem * child) {



    if (!child || child_map.find(child) != child_map.end()){
        return false;
    }

    std::list<BaseItem *>::iterator iter = childs.insert(childs.end(), child);
    child_map.insert(
        std::map<BaseItem *, std::list<BaseItem *>::iterator>::value_type(
            child, iter));
    return true;
}


bool BaseItem::RemoveChild(BaseItem * child){
     if (!child){
         return true;
     }
     std::map<BaseItem *, std::list<BaseItem *>::iterator>::iterator iter =
        child_map.find(child);
    
     if (iter == child_map.end()){
         return false;
     }
     childs.erase(iter->second);
    return true;
}