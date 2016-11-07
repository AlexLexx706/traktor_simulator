#ifndef __TRACE__
#define __TRACE__
#include <iostream>
#include <string>

struct BlockTrace{
    std::string name;
    BlockTrace(const std::string & _name):name(_name){
        std::cout << name << " >>"  << std::endl;
    }
    ~BlockTrace(){
        std::cout << name << " <<"  << std::endl;
    }
};

#endif // __TRACE__