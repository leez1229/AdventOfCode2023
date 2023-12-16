#pragma once

#include <stack>
#include <istream>
#include <map>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>
#include <set>
#include <array>

namespace Part1
{
    enum class Direction
    {
        UP,
        LEFT,
        DOWN,
        RIGHT,
        RIGHT_LEFT,
        UP_DOWN,
        STOP
    };
    struct Tile
    {
        char tile;
        bool energized;
        std::map<Direction,bool> visitedDirections{
            {Direction::UP,false},
            {Direction::LEFT,false},
            {Direction::DOWN,false},
            {Direction::RIGHT,false},
            {Direction::RIGHT_LEFT,false},
            {Direction::UP_DOWN,false}
        };
        Direction GetOutDirection(Direction in)
        {
            if(visitedDirections[in])
                return Direction::STOP;

            energized = true;
            visitedDirections[in] = true;

            if(tile == '.')
                return in;

            if(in == Direction::DOWN)
                return HandleDown();
            else if(in == Direction::UP)
                return HandleUp();
            else if(in == Direction::LEFT)
                return HandleLeft();
            else
                return HandleRight();
        }
        private:
            Direction HandleDown()
            {
                switch (tile)
                {
                case '|':
                    return Direction::DOWN;
                case '/':
                    return Direction::LEFT;
                case '\\':
                    return Direction::RIGHT;
                case '-':
                    return Direction::RIGHT_LEFT;
                }
            }
            Direction HandleUp()
            {
                switch (tile)
                {
                case '|':
                    return Direction::UP;
                case '/':
                    return Direction::RIGHT;
                case '\\':
                    return Direction::LEFT;
                case '-':
                    return Direction::RIGHT_LEFT;
                }
            }
            Direction HandleLeft()
            {
                switch (tile)
                {
                case '|':
                    return Direction::UP_DOWN;
                case '/':
                    return Direction::DOWN;
                case '\\':
                    return Direction::UP;
                case '-':
                    return Direction::LEFT;
                }
            }
            Direction HandleRight()
            {
                switch (tile)
                {
                case '|':
                    return Direction::UP_DOWN;
                case '/':
                    return Direction::UP;
                case '\\':
                    return Direction::DOWN;
                case '-':
                    return Direction::RIGHT;
                }
            }
    };
    class Work
    {
    public:
        Work();
        std::size_t Output();
        friend std::istream& operator>>(std::istream& istream, Part1::Work& work);
    private:
        std::vector<std::vector<Tile>> input;
        void ProgressBeam(int y, int x,Direction dir);
        bool VerifyValid(int y, int x);
        
    };
}