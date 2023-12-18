#include "Part2.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    long long int Shoelace(const Part2::Verticies v1, const Part2::Verticies& v2)
    {
        long long int xy1 = v1.x * v2.y;
        long long int xy2 = v1.y * v2.x;
        return xy1 - xy2;
    }
    //Solve for interor
    long long int Picks(long long int area,long long int b)
    {
        return (area + 1) - (b / 2);
    }
}

Part2::Work::Work()
{
}

std::size_t Part2::Work::Output()
{
    long long int sum {0};
    for(int i = 0; i < plane.size()-1;++i)
    {
        sum += Shoelace(plane[i],plane[i+1]);
    }
    sum += Shoelace(plane.back(),plane.front());
    long long int i = Picks (sum/2,perimiter);
    return i + perimiter;
}

namespace Part2
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        {
            char dir;
            istream >> dir;
            int count;
            istream >> count;
        }
        std::string colorCode;
        istream >> colorCode;
        std::string strCount = colorCode.substr(2,5);
        char strDir = colorCode.at(7);

        int count = std::stoi(strCount,0,16);
        int dirNum = std::stoi(std::string{strDir},0,16);
        
        char dir;
        if(dirNum == 0)
            dir = 'R';
        else if(dirNum == 1)
            dir = 'D';
        else if(dirNum == 2)
            dir = 'L';
        else
            dir = 'U';

        long long int xDir = 0;
        long long int yDir = 0;
        long long int shiftX = 0;
        long long int shiftY = 0;
        if(dir == 'R')
        {
            xDir = 1;
            shiftY = -1;
        }
        else if(dir == 'L')
        {
            xDir = -1;
            shiftY = 1;
        }
        else if(dir == 'D')
        {
            yDir = 1;
        }
        else if(dir == 'U')
            yDir = -1;
        if(work.plane.empty())
        {
            work.plane.push_back(Verticies{0,0,colorCode});
        }
        work.perimiter += count;
        Verticies& v = work.plane.back();
        work.plane.push_back(Verticies{v.y+(count*yDir),v.x+(count*xDir),colorCode});
    
        return istream;
    }
}