#include "Part2.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
}

Part2::Work::Work()
{
}

std::size_t Part2::Work::Output()
{
    Path initial;
    initial.currentTile = {0,0};
    // initial.debugPath.push_back(initial.currentTile);
    initial.heatLoss = 0;
    initial.previousDirection = Direction::Right;
    pQueue.push(initial);
    initial.previousDirection = Direction::DOWN;
    pQueue.push(initial);
    RunPaths();
    auto tempInput = input;
    // for(auto& debugPath: p.debugPath)
    // {
    //     std::cout << "(" << debugPath.second << ',' << debugPath.first << ") -> ";
    //     tempInput[debugPath.first][debugPath.second] = 0;
    // }
    // std::cout << '\n';
    // for(auto& row: distances)
    // {
        
    //     for(std::vector<std::array<int,11>> dir: row)
    //     {
    //         int min {999999};
    //         for(std::array<int,11> state: dir)
    //             for(int tile: state)
    //                 if(tile < min && tile != -1)
    //                     min = tile;
    //         std::cout << min << ' ';
    //     }
    //     std::cout << '\n';
    // }

    std::vector<int> values;
    auto& directionBottomRight = distances.back().back();
    for(std::array<int,11>& ary: directionBottomRight)
    {
        for(int i = 4; i < ary.size();++i)
        {
            if(ary[i] != -1)
                values.push_back(ary[i]);
        }
    }
    return *std::min_element(values.begin(),values.end());
}
std::vector<Part2::Path> Part2::Work::GetPossiblePaths(const Path& path)
{
    std::vector<Path> paths;
    int y = path.currentTile.first;
    int x = path.currentTile.second;
    const std::array<int,4> Y_DIRS = {-1,1,0,0};
    const std::array<int,4> X_DIRS = {0,0,-1,1};
    std::array<std::pair<Direction,Direction>,4> newDirections;
    newDirections[0] = {Direction::LEFT,Direction::Right};//Up
    newDirections[1] = {Direction::LEFT,Direction::Right};//Down
    newDirections[2] = {Direction::UP,Direction::DOWN};//Left
    newDirections[3] = {Direction::UP,Direction::DOWN};//Right
    
    //If going down, and we are not at 10 limit continue to go down
    //If going down, and >= 4 then we can do other paths
    if(path.inARowCount < 10)
    {
        //Continue in same direction
        Path p = path;
        p.currentTile = {p.currentTile.first+Y_DIRS[path.previousDirection],p.currentTile.second+X_DIRS[path.previousDirection]};
        if(p.currentTile.first >= 0 && p.currentTile.first <= input.size()-1)
        {
            if(p.currentTile.second >= 0 && p.currentTile.second <= input[p.currentTile.first].size()-1)
            {
                p.heatLoss += input[p.currentTile.first][p.currentTile.second];
                p.inARowCount++;
                paths.push_back(p);
            }
        }
    }

    
    if(path.inARowCount >= 4)
    {
        {
            auto directions = newDirections[path.previousDirection];
            Path p1 = path;
            p1.currentTile ={p1.currentTile.first+Y_DIRS[directions.first],p1.currentTile.second+X_DIRS[directions.first]};

            if(p1.currentTile.first >= 0 && p1.currentTile.first <= input.size()-1)
            {
                if(p1.currentTile.second >= 0 && p1.currentTile.second <= input[p1.currentTile.first].size()-1)
                {
                    p1.heatLoss += input[p1.currentTile.first][p1.currentTile.second];
                    p1.previousDirection = directions.first;
                    p1.inARowCount = 1;
                    paths.push_back(p1);
                }
            }
        }
        auto directions = newDirections[path.previousDirection];
        Path p2 = path;
        p2.currentTile ={p2.currentTile.first+Y_DIRS[directions.second],p2.currentTile.second+X_DIRS[directions.second]};

        if(p2.currentTile.first >= 0 && p2.currentTile.first <= input.size()-1)
        {
            if(p2.currentTile.second >= 0 && p2.currentTile.second <= input[p2.currentTile.first].size()-1)
            {
                p2.heatLoss += input[p2.currentTile.first][p2.currentTile.second];
                p2.previousDirection = directions.second;
                p2.inARowCount = 1;
                paths.push_back(p2);
            }
        }
    }
    return paths;
}

void Part2::Work::RunPaths()
{
    while(!pQueue.empty())
    {
        Path path = pQueue.top();
        pQueue.pop();
        int y = path.currentTile.first;
        int x = path.currentTile.second;
        std::vector<Path> possiblePaths = GetPossiblePaths(path);
        if(path.previousDirection != Direction::NONE)
        {
            //visited[y][x][path.previousDirection] = true;
            int currentHeat = distances[y][x][path.previousDirection][path.inARowCount];
            if(currentHeat != -1 && path.heatLoss > currentHeat)
               continue;
        }
        for(Path& p: possiblePaths)
        {
            int nextY = p.currentTile.first;
            int nextX = p.currentTile.second;
            int& historicHeatLoss = distances[nextY][nextX][p.previousDirection][p.inARowCount];
            if( historicHeatLoss == -1 || historicHeatLoss > p.heatLoss)
            {
                historicHeatLoss = p.heatLoss;
                pQueue.push(p);
            }
        }
    }
}

namespace Part2
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        std::string input;
        istream >> input;
        std::vector<int> row;
        std::vector<std::vector<std::array<int,11>>> distRow;
        std::vector<std::array<bool,4>> visited;
        for(char c: input)
        {
            row.push_back(std::atoi(&c));
            
            distRow.push_back({{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                            {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                            {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                            {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}});
            visited.push_back({false,false,false,false});
        }
        work.input.push_back(row);
        work.distances.push_back(distRow);
        work.visited.push_back(visited);
        return istream;
    }
}