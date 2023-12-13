#include "Part2.h"
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

    void Print(std::vector<std::vector<char>>& graph)
    {
        for(std::vector<char> row: graph)
        {
            for(char c: row)
            {
                std::cout << c;
            }
            std::cout << '\n';
        }
    }

    std::pair<std::size_t,std::size_t> IsInRightLoop(std::pair<std::size_t,std::size_t> pos, Direction heading)
    {
        if(heading == Direction::EAST)
        {
            pos.first++;
        }
        else if(heading == Direction::WEST)
        {
            pos.first--;
        }
        else if(heading == Direction::NORTH)
        {
            pos.second++;
        }
        else if(heading == Direction::SOUTH)
        {
            pos.second--;
        }
        return pos;
    }

    std::pair<std::size_t,std::size_t> IsInLeftLoop(std::pair<std::size_t,std::size_t> pos, Direction heading)
    {
        if(heading == Direction::EAST)
        {
            pos.first--;
        }
        else if(heading == Direction::WEST)
        {
            pos.first++;
        }
        else if(heading == Direction::NORTH)
        {
            pos.second--;
        }
        else if(heading == Direction::SOUTH)
        {
            pos.second++;
        }
        return pos;
    }

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

    bool Fill(std::vector<std::vector<char>>& graph)
    {
        bool repeate = false;
        for(std::size_t y = 0; y < graph.size();++y)
        {
            for(std::size_t x = 0; x < graph[y].size();++x)
            {
                char c = graph[y][x];
                if(c == '*')
                {
                    int up = y - 1;
                    int down = y + 1;
                    int left = x - 1;
                    int right = x + 1;
                    if(up >= 0 && graph[up][x] == '.')
                    {
                        graph[up][x] = '*';
                        repeate =  true;
                    }
                    if(down < graph.size() && graph[down][x] == '.')
                    {
                        graph[down][x] = '*';
                        repeate =  true;
                    }
                    if(left >= 0 && graph[y][left] == '.')
                    {
                        graph[y][left] = '*';
                        repeate =  true;
                    }
                    if(right < graph[y].size() && graph[y][right] == '.')
                    {
                        graph[y][right] = '*';
                        repeate =  true;
                    }
                }
            }
        }
        return repeate;
    }
    std::size_t Count(const std::vector<std::vector<char>>& graph)
    {
        std::size_t sum {0};
        for(std::size_t y = 0; y < graph.size();++y)
        {
            for(std::size_t x = 0; x < graph[y].size();++x)
            {
                if(graph[y][x] == '*')
                {
                    sum++;
                }
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
    bool toTheRight = true;
    Direction startDirection = Direction::NORTH;

    std::pair<std::size_t,std::size_t> pos;

    {
        for(int y = 0; y < graph.size(); ++y)
        {
            for(int x = 0; x < graph[y].size();++x)
            {
                if(graph[y][x] == 'S')
                {
                    pos = {y,x};
                    loop[pos.first][pos.second] = true;
                    break;
                }
            }
        }
        std::pair<std::size_t,std::size_t> checkPos;
    
        //SHORTCUT prime the Start
        
        pos = Step(startDirection,pos);
        loop[pos.first][pos.second] = true;
        Direction dir = Navigate(FromTo(startDirection),graph[pos.first][pos.second]);
        //Priming Done
        while(graph[pos.first][pos.second] != 'S')
        {
            pos = Step(dir,pos);
            loop[pos.first][pos.second] = true;
            dir = Navigate(FromTo(dir),graph[pos.first][pos.second]);
        }

        for(int y = 0; y < loop.size(); ++y)
        {
            for(int x = 0; x < loop[y].size();++x)
            {
                if(!loop[y][x])
                {
                    graph[y][x] = '.';
                }
            }
        }
    }

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
    std::pair<std::size_t,std::size_t> checkPos;
    if(toTheRight)
        checkPos = IsInRightLoop(pos,startDirection);
    else
        checkPos = IsInLeftLoop(pos,startDirection);
    if(graph[checkPos.first][checkPos.second] == '.')
    {
        graph[checkPos.first][checkPos.second] = '*';
    }
   
    //SHORTCUT prime the Start
    
    pos = Step(startDirection,pos);
    Direction dir = Navigate(FromTo(startDirection),graph[pos.first][pos.second]);
    //Priming Done
    if(toTheRight)
        checkPos = IsInRightLoop(pos,startDirection);
    else
        checkPos = IsInLeftLoop(pos,startDirection);
    if(graph[checkPos.first][checkPos.second] == '.')
    {
        graph[checkPos.first][checkPos.second] = '*';
    }
    while(graph[pos.first][pos.second] != 'S')
    {
        pos = Step(dir,pos);
        dir = Navigate(FromTo(dir),graph[pos.first][pos.second]);
        if(toTheRight)
            checkPos = IsInRightLoop(pos,dir);
        else
            checkPos = IsInLeftLoop(pos,dir);
        if(graph[checkPos.first][checkPos.second] == '.')
        {
            graph[checkPos.first][checkPos.second] = '*';
        }
    }
    
    while(Fill(graph));
    Print(graph);
    return Count(graph);
}


namespace Part2
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        char c;
        istream >>  c;
        std::vector<char> row;
        std::vector<bool> loopRow;
        while(istream)
        {
            loopRow.push_back(false);
            if(c == 'S')
            {
                //y,x
                work.start = {work.graph.size(),row.size()};
            }
            row.push_back(c);
            istream >> c;
        }
        work.graph.push_back(row);
        work.loop.push_back(loopRow);
        return istream;
    }
}