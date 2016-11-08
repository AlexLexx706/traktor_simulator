#ifndef __TRACE__
#define __TRACE__
#include <iostream>
#include <string>

struct BlockTrace{
    std::string name;
    BlockTrace(const std::string & _name):name(_name){
        std::cerr << name << " >>"  << std::endl;
    }
    ~BlockTrace(){
        std::cerr << name << " <<"  << std::endl;
    }
};

#endif // __TRACE__