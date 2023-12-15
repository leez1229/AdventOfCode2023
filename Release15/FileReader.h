#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class FileReader
{
public:
    FileReader(const std::string& path,const std::string& deliminator);
    ~FileReader();
    template <class T>
    bool ParseToObject(T& obj)
    {
        bool readLines = false;
        if(file)
        {
            std::string line;
            std::getline(file,line);
            while(file && (line != deliminator))
            {
                std::istringstream ss(line);
                ss >>  obj;
                readLines = true;
                std::getline(file,line);
            }
        }
        return readLines;
    }
private:
    std::ifstream file;
    const std::string& deliminator;
};