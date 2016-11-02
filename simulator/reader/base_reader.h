#ifndef __BASE_READER__
#define __BASE_READER__

class BaseReader{
public:
    BaseReader(){};
    virtual ~BaseReader(){};
    virtual int read(void * buffer, unsigned int buffer_size) = 0;
};

#endif