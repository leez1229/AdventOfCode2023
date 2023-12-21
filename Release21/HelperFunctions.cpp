#include "HelperFunctions.h"

std::vector<std::string> Split(const std::string& str, char delim)
{
    std::vector<std::string> split;
    std::size_t pos = str.find_first_of(delim);
    std::size_t startPos = 0;
    while(pos != std::string::npos)
    {
        split.push_back(str.substr(startPos,pos-startPos));
        startPos = pos + 1;
        pos = str.find_first_of(delim,startPos);
    }
    if(startPos < str.length())
    {
        split.push_back(str.substr(startPos));
    }
    
    return split;
}

std::size_t GCF(std::size_t a, std::size_t b)
{
    if(a > b)
    {
        std::size_t temp = a;
        a = b;
        b = temp;
    }
    std::size_t gcf {0};
    for(std::size_t i = 1; i < a; i++)
    {
        if(a % i == 0 && b % i == 0)
        {
            gcf = i;
        }
    }
    return gcf;
}

std::size_t LCM(std::size_t a, std::size_t b)
{
    return a * b / GCF(a,b);
}