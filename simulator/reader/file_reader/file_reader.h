#ifndef __SIM_FILE_READER__
#define __SIM_FILE_READER__
#include "../base_reader.h"

class FileReader: public BaseReader{
public:
    FileReader();
    ~FileReader();
    virtual int read(void * buffer, unsigned int buffer_size);
private:
    int test;
};

#endif