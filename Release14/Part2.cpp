#include "Part2.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    void Print(std::vector<std::vector<char>>& platform)
    {
        for(std::size_t y = 0; y < platform.size();++y)
        {
            for(std::size_t x = 0; x < platform[y].size();++x)
            {
                std::cout << platform[y][x];
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    void MoveNorth(std::vector<std::vector<char>>& platform)
    {
        bool isMovement{false};
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
    void MoveWest(std::vector<std::vector<char>>& platform)
    {
        bool isMovement{false};
        for(std::size_t y = 0; y < platform.size();++y)
        {
            for(std::size_t x = 0; x < platform[y].size();++x)
            {
                char& c = platform[y][x];
                if(c == 'O')
                {
                    
                    if(x > 0 && platform[y][x-1] == '.')
                    {
                        c = '.';
                        platform[y][x-1] = 'O';
                        isMovement = true;
                    }
                }
            }
        }
        if(isMovement)
            MoveWest(platform);
    }
    void MoveSouth(std::vector<std::vector<char>>& platform)
    {
        bool isMovement{false};
        for(int y = platform.size()-1; y >= 0;--y)
        {
            for(int x = 0; x < platform[y].size();++x)
            {
                char& c = platform[y][x];
                if(c == 'O')
                {
                    
                    if(y < platform.size()-1 && platform[y+1][x] == '.')
                    {
                        c = '.';
                        platform[y+1][x] = 'O';
                        isMovement = true;
                    }
                }
            }
        }
        if(isMovement)
            MoveSouth(platform);
    }
    void MoveEast(std::vector<std::vector<char>>& platform)
    {
        bool isMovement {false};
        for(int y = 0; y < platform.size();++y)
        {
            for(int x = platform[y].size()-1; x >= 0;--x)
            {
                char& c = platform[y][x];
                if(c == 'O')
                {
                    
                    if(x < platform[y].size()-1 && platform[y][x+1] == '.')
                    {
                        c = '.';
                        platform[y][x+1] = 'O';
                        isMovement = true;
                    }
                }
            }
        }
        if(isMovement)
            MoveEast(platform);
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
    std::string CreateKey(std::vector<std::vector<char>>& platform)
    {
        std::string key;
        for(std::size_t y = 0; y < platform.size();++y)
        {
            for(std::size_t x = 0; x < platform[y].size();++x)
            {
                key.push_back((platform[y][x]));
            }
        }
        return key;
    }
}

Part2::Work::Work()
{
}

std::size_t Part2::Work::Output()
{
    std::size_t fastFwd{0};
    for(std::size_t i = 0; i < 1000000000;++i)
    {
        //Print(platform);
        MoveNorth(platform);//North
        //Print(platform);
        MoveWest(platform);//West
        //Print(platform);
        MoveSouth(platform);
        //Print(platform);
        MoveEast(platform);
        //Print(platform);
        if(fastFwd == 0)
        {
            std::string key = CreateKey(platform);
            auto it = cycleCache.find(key);
            if(it != cycleCache.end())
            {
                int diff = (i - it->second);
                //9
                //2
                int cyclesLeft = ((1000000000 - i) % diff);
                fastFwd = 1000000000 - cyclesLeft;
                // while(fastFwd < 1000000000 - it->second)
                // {
                //     //fastFwd += (i - it->second);
                // }
                i = fastFwd;
            }
            std::cout << i << " " << CountLoad(platform) << '\n';
            cycleCache[key] = i;
        }
    }
    
    return CountLoad(platform);
}

namespace Part2
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