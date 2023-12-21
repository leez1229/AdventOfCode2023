#include "Part2.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    void Print(std::vector<std::vector<char>>& map)
    {
        for(auto& v: map)
        {
            for(char c: v)
            {
                std::cout << c;
            }
            std::cout << '\n'; 
        }
        std:: cout << "\n\n";
    }

    std::size_t Count(std::vector<std::vector<char>>& map)
    {
        std::size_t sum{0};
        for(auto& v: map)
        {
            for(char c: v)
            {
                if(c == 'O')
                    ++sum;
            }
        }
        return sum;
    }

    void SetSurroundings(std::size_t y, std::size_t x, std::vector<std::vector<char>>& map)
    {
        //Up
        if(y > 0)
        {
           char& c = map[y-1][x];
           if(c != '#')
           {
                c = 'O';
           }
        }
        //Down
        if(y < map.size() - 1)
        {
           char& c = map[y+1][x];
           if(c != '#')
           {
                c = 'O';
           }
        }
        //Right
        if(x < map[y].size() - 1)
        {
           char& c = map[y][x+1];
           if(c != '#')
           {
                c = 'O';
           }
        }
        //Left
        if(x > 0)
        {
           char& c = map[y][x-1];
           if(c != '#')
           {
                c = 'O';
           }
        }
    }
}

Part2::Work::Work()
{
}

std::size_t Part2::Work::Output()
{
    std::vector<std::vector<char>> iterationMap;
    //65
    //196
    //327

    //26501365 steps so find number of walk positions
    //26501365 - 65 = 26501300
    //26501300 / 131 = 202300
    //x = 202300
    //f(n) = f(65) + f(196) + f(327)
    std::size_t steps{26501365};
    std::vector<int> abc;
    for(int i  = 0; i < steps; ++i)
    {
        auto mapCopy = map;
        
        if(i == 0)
        {
            iterationMap = map;
            iterationMap[startPos.first][startPos.second] = 'O';
        }
        
        for(std::size_t y = 0; y < iterationMap.size(); ++y)
        {
            for(std::size_t x = 0; x < iterationMap[y].size();++x)
            {
                if(iterationMap[y][x] == 'O')
                {
                    SetSurroundings(y,x,mapCopy);
                }
            }
        }
        iterationMap = mapCopy;
        //manually increase the maps perimiter 4 times
        //This squares the area each time for a total of 2 times
        //131 * 2 = 262
        //131 * 4 = 524
        //map size is 524
        //26501365 % 524 = 65
        //65 Because that would mean we came from the center and now on the edge of the map perimter doubled
        //if(i % (65 + (65 * abc.size())) == steps % map.size())
        if(i+1 == 65 + 131 * abc.size())
        {
            abc.push_back(Count(iterationMap));
        }
        if(abc.size() == 3)
            break;
        //Print(iterationMap);
    }

    std::cout << "x = 2, y = " << abc[2] << '\n';
    std::cout << "x = 1, y = " << abc[1] << '\n';
    std::cout << "x = 0, y = " << abc[0] << '\n';
    //Do quadratic best fit
    //Used wolfram
    //Uses the data points to find an quadratic equation from the data set
    std::size_t x = (steps - 65) / 131;
    return 3730 + 14863 * x + 14773 * x*x;
}

namespace Part2
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        std::string line;
        istream >> line;
        std::vector<char> row;
        for(char c: line)
        {
            if(c == 'S')
            {
                c = '.';
                work.startPos = {work.map.size(),row.size()};
            }
            row.push_back(c);
        }
        work.map.push_back(row);
        return istream;
    }
}