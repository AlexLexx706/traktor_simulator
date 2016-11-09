#ifndef __SCENE__
#define __SCENE__
#include <list>
#include <map>
#include <string>
#include "../../common/SMat.h"
#include "../../common/types.h"

class Camera;
class BaseShape;

class Scene{
public:
    //отображение текста в сцене
    class Text{
    public:
        Text(const std::string & _str, const SVec & _pos, void * _font=NULL):
            str(_str), font(_font), pos(_pos),color(1,0,0,1){
        }
        void set_text(const std::string & _str) {str=_str;}
        std::string get_text() const {return str;}
        void set_pos(const SVec & _pos){pos=_pos;}
        SVec get_pos() const {return pos;}
        Color get_color() const {return color;}
        void set_color(const Color & _color) {color=_color;}
    private:
        friend Scene;
        std::string str;
        void *font;
        SVec pos;
        Color color;
    };

    Scene();
    ~Scene();
    virtual void update();
    bool add_shape(BaseShape * shape);
    bool remove_shape(BaseShape * shape);
    double get_dt() const {return dt;};
    std::list<BaseShape *> & get_shapes(){return shapes;}
    Camera * get_camera() const {return camera;}
    bool add_text(Text * text);
    bool remove_text(Text * text);
protected:
    std::list<BaseShape *> shapes;
    std::map<BaseShape *, std::list<BaseShape *>::iterator> shapes_map;
    
    int last_time;
    double dt;
    Camera * camera;
    std::list<Text *> texts;
    std::map<Text *, std::list<Text *>::iterator> texts_map;
    
    void UpdateAR(int w, int h);
    void updateDT();
    void draw_text(void *font, double x, double y, const std::string & str);
};
#endif // __BASE_ITEM__


