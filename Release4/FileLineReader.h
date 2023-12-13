#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class FileLineReader
{
public:
    FileLineReader(const std::string& path,const std::string& deliminator);
    ~FileLineReader();
    template <class T>
    bool ParseToObject(T& obj, int lineCount = 1)
    {
        bool readLines = false;
        if(file)
        {
            std::string output;
            for(int i = 0; i < lineCount; ++i)
            {
                std::string line;
                std::getline(file,line);
                if(!line.empty() && file)
                {
                    if(!output.empty())
                    {
                        output += " ";
                    }
                    output += line;
                    readLines = true;
                }
                else
                {
                    break;
                }
            }
            if(readLines)
            {
                std::istringstream ss(output);
                ss >>  obj;
            }
        }
        return readLines;
    }
private:
    std::ifstream file;
    const std::string& deliminator;
};