#include "Part1.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    void MoveNorth(std::vector<std::vector<char>>& platform)
    {
        bool isMovement {false};
        for(std::size_t y = 0; y < platform.size();++y)
        {
            for(std::size_t x = 0; x < platform[y].size();++x)
            {
                char& c = platform[y][x];
                if(c == 'O')
                {
                    
                    if(y > 0 && platform[y-1][x] == '.')
                    {
                        c = '.';
                        platform[y-1][x] = 'O';
                        isMovement = true;
                    }
                }
            }
        }
        if(isMovement)
            MoveNorth(platform);
    }

    std::size_t CountLoad(std::vector<std::vector<char>>& platform)
    {
        std::size_t sum {0};
        for(std::size_t y = 0; y < platform.size();++y)
        {
            for(std::size_t x = 0; x < platform[y].size();++x)
            {
                if(platform[y][x] == 'O')
                {
                    sum += platform.size() - y;
                }
            }
        }
        return sum;
    }
}

Part1::Work::Work()
{
}

std::size_t Part1::Work::Output()
{
    MoveNorth(platform);
    return CountLoad(platform);
}

namespace Part1
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        int i = 0;
        char c;
        istream >> c;
        std::vector<char> row;
        
        while(istream)
        {
            row.push_back(c);
            istream >> c;
        }
        work.platform.push_back(row);

        return istream;
    }
}