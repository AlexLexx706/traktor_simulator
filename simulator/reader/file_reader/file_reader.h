#ifndef __SIM_FILE_READER__
#define __SIM_FILE_READER__
#include "../base_reader.h"

class FileReader: public BaseReader{
public:
    FileReader();
    ~FileReader();
    bool open(const char* file_name, std::size_t max_count=0);
    virtual const std::list<BaseReader::Data> & get_gata() const {return data;};
private:
    std::list<BaseReader::Data> data;
};

#endif