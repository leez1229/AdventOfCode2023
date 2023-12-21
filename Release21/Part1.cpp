#include "Part1.h"
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

Part1::Work::Work()
{
}

std::size_t Part1::Work::Output()
{
    std::vector<std::vector<char>> iterationMap;
    for(int i  = 0; i < 65; ++i)
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
        //Print(iterationMap);
    }
    return Count(iterationMap);
}

namespace Part1
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