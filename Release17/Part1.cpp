#include "Part1.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
}

Part1::Work::Work()
{
}

std::size_t Part1::Work::Output()
{
    Path initial;
    initial.currentTile = {0,0};
    // initial.debugPath.push_back(initial.currentTile);
    initial.heatLoss = 0;
    pQueue.push(initial);
    RunPaths();
    auto tempInput = input;
    // for(auto& debugPath: p.debugPath)
    // {
    //     std::cout << "(" << debugPath.second << ',' << debugPath.first << ") -> ";
    //     tempInput[debugPath.first][debugPath.second] = 0;
    // }
    // std::cout << '\n';
    for(auto& row: distances)
    {
        
        for(std::vector<std::array<int,4>> dir: row)
        {
            int min {999999};
            for(std::array<int,4> state: dir)
                for(int tile: state)
                    if(tile < min && tile != -1)
                        min = tile;
            std::cout << min << ' ';
        }
        std::cout << '\n';
    }
    return 0;//distances.back().back();
}
std::vector<Part1::Path> Part1::Work::GetPossiblePaths(const Path& path)
{
    std::vector<Path> paths;
    int y = path.currentTile.first;
    int x = path.currentTile.second;
    //GO Down
    if(path.previousDirection != Direction::UP && y < input.size()-1)
    {
        Path p = path;
        p.currentTile = {p.currentTile.first+1,p.currentTile.second};
        // p.debugPath.push_back(p.currentTile);
        p.previousDirection = Direction::DOWN;
        p.heatLoss += input[p.currentTile.first][p.currentTile.second];
        if(p.inARowDirection != Direction::DOWN)
        {
            p.inARowDirection = Direction::DOWN;
            p.inARowCount = 1;
        }
        else
        {
            p.inARowCount++;
        }
        if(p.inARowCount <= 3 && !visited[p.currentTile.first][p.currentTile.second][p.previousDirection])
            paths.push_back(p);
    }
    //GO Up
    if(path.previousDirection != Direction::DOWN && y > 0)
    {
        Path p = path;
        p.currentTile = {p.currentTile.first-1,p.currentTile.second};
        // p.debugPath.push_back(p.currentTile);
        p.previousDirection = Direction::UP;
        p.heatLoss += input[p.currentTile.first][p.currentTile.second];
        if(p.inARowDirection != Direction::UP)
        {
            p.inARowDirection = Direction::UP;
            p.inARowCount = 1;
        }
        else
        {
            p.inARowCount++;
        }
        if(p.inARowCount <= 3 && !visited[p.currentTile.first][p.currentTile.second][p.previousDirection])
            paths.push_back(p);
    }
    //Go Right
    if(path.previousDirection != Direction::LEFT && x < input[y].size()-1)
    {
        Path p = path;
        p.currentTile = {p.currentTile.first,p.currentTile.second+1};
        // p.debugPath.push_back(p.currentTile);
        p.previousDirection = Direction::Right;
        p.heatLoss += input[p.currentTile.first][p.currentTile.second];
        if(p.inARowDirection != Direction::Right)
        {
            p.inARowDirection = Direction::Right;
            p.inARowCount = 1;
        }
        else
        {
            p.inARowCount++;
        }
        if(p.inARowCount <= 3 && !visited[p.currentTile.first][p.currentTile.second][p.previousDirection])
            paths.push_back(p);
    }

    //Go Left
    if(path.previousDirection != Direction::Right && x > 0)
    {
        Path p = path;
        p.currentTile = {p.currentTile.first,p.currentTile.second-1};
        // p.debugPath.push_back(p.currentTile);
        p.previousDirection = Direction::LEFT;
        p.heatLoss += input[p.currentTile.first][p.currentTile.second];
        if(p.inARowDirection != Direction::LEFT)
        {
            p.inARowDirection = Direction::LEFT;
            p.inARowCount = 1;
        }
        else
        {
            p.inARowCount++;
        }
        if(p.inARowCount <= 3 && !visited[p.currentTile.first][p.currentTile.second][p.previousDirection])
            paths.push_back(p);
    }
    return paths;
}

void Part1::Work::RunPaths()
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
            if(path.heatLoss > distances[y][x][path.previousDirection][path.inARowCount])
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

namespace Part1
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        std::string input;
        istream >> input;
        std::vector<int> row;
        std::vector<std::vector<std::array<int,4>>> distRow;
        std::vector<std::array<bool,4>> visited;
        for(char c: input)
        {
            row.push_back(std::atoi(&c));
            
            distRow.push_back({{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1}});
            visited.push_back({false,false,false,false});
        }
        work.input.push_back(row);
        work.distances.push_back(distRow);
        work.visited.push_back(visited);
        return istream;
    }
}