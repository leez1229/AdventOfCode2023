#include "Part1.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    int Shoelace(const Part1::Verticies v1, const Part1::Verticies& v2)
    {
        int xy1 = v1.x * v2.y;
        int xy2 = v1.y * v2.x;
        return xy1 - xy2;
    }
    //Solve for interor
    int Picks(int area,int b)
    {
        return (area + 1) - (b / 2);
    }
}

Part1::Work::Work()
{
}

std::size_t Part1::Work::Output()
{
    int sum {0};
    for(int i = 0; i < plane.size()-1;++i)
    {
        sum += Shoelace(plane[i],plane[i+1]);
    }
    sum += Shoelace(plane.back(),plane.front());
    int i = Picks (sum/2,perimiter);
    return i + perimiter;
}

namespace Part1
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        char dir;
        istream >> dir;
        int count;
        istream >> count;
        std::string colorCode;
        istream >> colorCode;
        int xDir = 0;
        int yDir = 0;
        int shiftX = 0;
        int shiftY = 0;
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