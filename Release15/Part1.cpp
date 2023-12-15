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
    std::size_t sum{0};
    for(auto& str: input)
    {
        int currentValue = 0;
        for(char c: str)
        {
            currentValue += c;
            currentValue *= 17;
            currentValue %= 256;
        }
        sum += currentValue;
    }
    return sum;
}

namespace Part1
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
       std::string input;
       istream >> input;
       work.input = Split(input,',');

        return istream;
    }
}