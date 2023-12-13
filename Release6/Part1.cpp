#include "Part1.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    int LowerBound(int time, int targetDistance)
    {
        for(int i = 0; i <= time;++i)
        {
            if(i * (time - i) > targetDistance)
            {
                return i;
            }
        }
        return -1;
    }

    int UpperBound(int time, int targetDistance)
    {
        for(int i = time; i >= 0;--i)
        {
            if(i * (time - i) > targetDistance)
            {
                return i;
            }
        }
        return -1;
    }
}

Part1::Work::Work()
{
}

std::size_t Part1::Work::Output()
{
    int mp {0};
    for(int i = 0; i < time.size();++i)
    {
        int t = time[i];
        int d = distance[i];
        int upperBound = UpperBound(t,d);
        int lowerBound = LowerBound(t,d);
        int ways = (upperBound - lowerBound) + 1;
        if(mp == 0)
            mp = ways;
        else
            mp *= ways;
    }
    return mp;
}


namespace Part1
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        std::string desc;
        istream >> desc;
        std::vector<int>* values;
        int value;
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