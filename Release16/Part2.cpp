#include "Part2.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    void Print(const std::vector<std::vector<Part2::Tile>>& input)
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
    std::size_t Count(const std::vector<std::vector<Part2::Tile>>& input)
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

Part2::Work::Work()
{
}

std::size_t Part2::Work::Output()
{
    //TopRow
    for(int x = 0; x < input[0].size();++x)
    {
        auto inputCopy = input;
        ProgressBeam(0,x,Direction::DOWN,inputCopy);
        counts.push_back(Count(inputCopy));
    }
    //Left Col
    for(int y = 0; y < input.size();++y)
    {
        auto inputCopy = input;
        ProgressBeam(y,0,Direction::RIGHT,inputCopy);
        counts.push_back(Count(inputCopy));
    }
    //Bottom Row
    for(int x = 0; x < input[input.size()-1].size();++x)
    {
        auto inputCopy = input;
        ProgressBeam(input.size()-1,x,Direction::UP,inputCopy);
        counts.push_back(Count(inputCopy));
    }
    //Right Col
    for(int y = 0; y < input.size();++y)
    {
        auto inputCopy = input;
        ProgressBeam(y,input[y].size()-1,Direction::LEFT,inputCopy);
        counts.push_back(Count(inputCopy));
    }
    
    //Print(input);
    return *std::max_element(counts.begin(),counts.end());
}

void Part2::Work::ProgressBeam(int y, int x, Direction dir, std::vector<std::vector<Tile>>& grid)
{
    //PreConditions
    if(!VerifyValid(y,x))
        return;

    //PreConditions End

    Direction newDir = grid[y][x].GetOutDirection(dir);
    if(newDir == Direction::RIGHT)
        ProgressBeam(y,x+1,newDir,grid);
    else if(newDir == Direction::LEFT)
        ProgressBeam(y,x-1,newDir,grid);
    else if(newDir == Direction::UP)
        ProgressBeam(y-1,x,newDir,grid);
    else if(newDir == Direction::DOWN)
        ProgressBeam(y+1,x,newDir,grid);
    else if(newDir == Direction::UP_DOWN)
    {
        ProgressBeam(y-1,x,Direction::UP,grid);
        ProgressBeam(y+1,x,Direction::DOWN,grid);
    }
    else if(newDir == Direction::RIGHT_LEFT)
    {
        ProgressBeam(y,x+1,Direction::RIGHT,grid);
        ProgressBeam(y,x-1,Direction::LEFT,grid);
    }
}

bool Part2::Work::VerifyValid(int y, int x)
{
    return y >= 0 && y < input.size() && x >= 0 && x < input[y].size();
}

namespace Part2
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