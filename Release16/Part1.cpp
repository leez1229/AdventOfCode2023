#include "Part1.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    void Print(const std::vector<std::vector<Part1::Tile>>& input)
    {
        for(auto& row: input)
        {
            for(auto& t: row)
            {
                std::cout << t.energized;
            }
            std::cout << '\n';
        }
    }
    std::size_t Count(const std::vector<std::vector<Part1::Tile>>& input)
    {
        std::size_t sum{0};
        for(auto& row: input)
        {
            for(auto& t: row)
            {
                if(t.energized)
                    ++sum;
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
    ProgressBeam(0,0,Direction::RIGHT);
    //Print(input);
    return Count(input);
}

void Part1::Work::ProgressBeam(int y, int x, Direction dir)
{
    //PreConditions
    if(!VerifyValid(y,x))
        return;

    //PreConditions End

    Direction newDir = input[y][x].GetOutDirection(dir);
    if(newDir == Direction::RIGHT)
        ProgressBeam(y,x+1,newDir);
    else if(newDir == Direction::LEFT)
        ProgressBeam(y,x-1,newDir);
    else if(newDir == Direction::UP)
        ProgressBeam(y-1,x,newDir);
    else if(newDir == Direction::DOWN)
        ProgressBeam(y+1,x,newDir);
    else if(newDir == Direction::UP_DOWN)
    {
        ProgressBeam(y-1,x,Direction::UP);
        ProgressBeam(y+1,x,Direction::DOWN);
    }
    else if(newDir == Direction::RIGHT_LEFT)
    {
        ProgressBeam(y,x+1,Direction::RIGHT);
        ProgressBeam(y,x-1,Direction::LEFT);
    }
}

bool Part1::Work::VerifyValid(int y, int x)
{
    return y >= 0 && y < input.size() && x >= 0 && x < input[y].size();
}

namespace Part1
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
       std::string input;
       istream >> input;
        std::vector<Tile> row;
        for(char c: input)
        {
            row.push_back(Tile{c,false});
        }
        work.input.push_back(row);
        return istream;
    }
}