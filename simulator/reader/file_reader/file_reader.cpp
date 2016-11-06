#include "./file_reader.h"
#include <iostream>
#include <fstream>
#include "../../common/coordinat_converter/coordinat_converter.h"

FileReader::FileReader(){}
FileReader::~FileReader(){}

bool FileReader::open(const char* file_name, std::size_t max_count) {
    if (!file_name){
        std::cerr << "file_name == NULL" << std::endl;
        return false;
    }

    std::ifstream file;
    file.open(file_name);

    if (!file){
        std::cerr << "Cannot open file: " << file_name << std::endl;
        return false;
    }

    Data sample;
    double temp;
    int temp_int;
    data.clear();

    while(file) {
        file >> sample.time >> sample.ecef_pos.x0 >> sample.ecef_pos.x1 >> sample.ecef_pos.x2 >> temp >> temp >> temp >> sample.speed >> temp >> temp >> sample.azimut >> temp >> temp_int; 
        //std::cout << sample << std::endl;
        sample.ned_pos = ecef_to_ned(sample.ecef_pos.x0, sample.ecef_pos.x1, sample.ecef_pos.x2);
        data.push_back(sample);
        if (max_count > 0 and data.size() >= max_count){
            return true;
        }
    }
    return true;
}