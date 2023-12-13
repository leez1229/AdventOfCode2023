#include "HelperFunctions.h"

std::vector<std::string> Split(const std::string& str, char delim)
{
    std::vector<std::string> split;
    int pos = str.find_first_of(delim);
    std::size_t startPos = 0;
    while(pos != std::string::npos)
    {
        split.push_back(str.substr(startPos,pos));
        startPos = pos + 1;
        pos = str.find_first_of(delim,startPos);
    }
    if(startPos < str.length())
    {
        split.push_back(str.substr(startPos));
    }
    
    return split;
}