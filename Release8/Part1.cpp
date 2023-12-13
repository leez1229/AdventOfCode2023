#include "Part1.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
   
}

Part1::Work::Work()
{
}

std::size_t Part1::Work::Output()
{
    std::size_t sum {0};
    std::string currentPos = "AAA";
    std::size_t index {0};
    while(currentPos != "ZZZ")
    {
        std::pair<std::string,std::string>& choice = graph[currentPos];
        if(path[index] == 'R')
           currentPos = choice.second;
        else
            currentPos = choice.first;
        ++sum;
        index = ++index % path.size();
    }
    return sum;
}


namespace Part1
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        if(work.path.empty())
        {
            char p;
            istream >> p;
            while(istream)
            {
                work.path.push_back(p);
                istream >> p;
            }
        }
        else
        {
            std::string start;
            istream >> start;
            char garbage;
            istream >> garbage;
            istream >> garbage;
            std::string left;
            istream >> left;
            left = left.substr(0,left.size()-1);
            std::string right;
            istream >> right;
            right = right.substr(0,right.size()-1);
            work.graph[start] = {left,right};
        }

        return istream;
    }
}