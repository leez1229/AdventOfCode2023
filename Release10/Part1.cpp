#include "Part1.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    enum class Direction
    {
        NORTH,
        EAST,
        SOUTH,
        WEST,
        NONE
    };
    Direction FromTo(Direction from)
    {
        if(from == Direction::NORTH)
            return Direction::SOUTH;
        else if(from == Direction::SOUTH)
            return Direction::NORTH;
        else if(from == Direction::EAST)
            return Direction::WEST;
        else
            return Direction::EAST;
    }
    std::pair<std::size_t,std::size_t> Step(Direction direction,std::pair<std::size_t,std::size_t> location)
    {
        if(direction == Direction::NORTH)
            location.first--;
        else if(direction == Direction::SOUTH)
            location.first++;
        else if(direction == Direction::WEST)
            location.second--;
        else if(direction == Direction::EAST)
            location.second++;
        
        return location;
    }

    Direction Navigate(Direction direction, char c)
    {
        switch (c)
        {
        case '|':
            return direction == Direction::NORTH ? Direction::SOUTH : Direction::NORTH;
        case '-':
            return direction == Direction::EAST ? Direction::WEST : Direction::EAST;
        case 'L':
            return direction == Direction::NORTH ? Direction::EAST : Direction::NORTH;
        case 'J':
            return direction == Direction::NORTH ? Direction::WEST : Direction::NORTH;
        case '7':
            return direction == Direction::SOUTH ? Direction::WEST : Direction::SOUTH;
        case 'F':
            return direction == Direction::SOUTH ? Direction::EAST : Direction::SOUTH;
        default:
            return Direction::NONE;
        }
    }
}

Part1::Work::Work()
{
}

std::size_t Part1::Work::Output()
{
    std::size_t sum {0};
    std::pair<std::size_t,std::size_t> pos;
    for(int y = 0; y < graph.size(); ++y)
    {
        for(int x = 0; x < graph[y].size();++x)
        {
            if(graph[y][x] == 'S')
            {
                pos = {y,x};
            }
        }
    }
    //SHORTCUT prime the Start
    Direction startDirection = Direction::NORTH;
    pos = Step(startDirection,pos);
    ++sum;
    Direction dir = Navigate(FromTo(startDirection),graph[pos.first][pos.second]);
    //Priming Done
    while(graph[pos.first][pos.second] != 'S')
    {
        pos = Step(dir,pos);
        ++sum;
        dir = Navigate(FromTo(dir),graph[pos.first][pos.second]);
    }
    return sum/2;
}


namespace Part1
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        char c;
        istream >>  c;
        std::vector<char> row;
        while(istream)
        {
            if(c == 'S')
            {
                //y,x
                work.start = {work.graph.size(),row.size()};
            }
            row.push_back(c);
            istream >> c;
        }
        work.graph.push_back(row);
        return istream;
    }
}