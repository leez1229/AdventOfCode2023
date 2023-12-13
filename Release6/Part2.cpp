#include "Part2.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    std::size_t LowerBound(std::size_t time, std::size_t targetDistance)
    {
        for(std::size_t i = 0; i <= time;++i)
        {
            if(i * (time - i) > targetDistance)
            {
                return i;
            }
        }
        return -1;
    }

    std::size_t UpperBound(std::size_t time, std::size_t targetDistance)
    {
        for(std::size_t i = time; i >= 0;--i)
        {
            if(i * (time - i) > targetDistance)
            {
                return i;
            }
        }
        return -1;
    }
}

Part2::Work::Work()
{
}

std::size_t Part2::Work::Output()
{
    std::size_t mp {0};
    for(std::size_t i = 0; i < time.size();++i)
    {
        std::size_t t = time[i];
        std::size_t d = distance[i];
        std::size_t upperBound = UpperBound(t,d);
        std::size_t lowerBound = LowerBound(t,d);
        std::size_t ways = (upperBound - lowerBound) + 1;
        if(mp == 0)
            mp = ways;
        else
            mp *= ways;
    }
    return mp;
}


namespace Part2
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        std::string desc;
        istream >> desc;
        std::vector<std::size_t>* values;
        std::size_t value;
        istream >> value;
        if(desc == "Time:")
            values = &work.time;
        else
            values = &work.distance;
        while(istream)
        {
            values->push_back(value);
            istream >> value;
        }
        return istream;
    }
}