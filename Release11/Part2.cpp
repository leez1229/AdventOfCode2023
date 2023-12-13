#include "Part2.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    constexpr int GROW_SIZE = 1000000;
    void Print(const std::vector<std::vector<char>>& galaxy)
    {
        for(int y = 0;y < galaxy.size();y++) 
        {
            bool blank {true};
            for(int x = 0; x < galaxy[y].size();x++)
            {
                std::cout << galaxy[y][x];
            }
            std::cout << '\n';
        }
    }
    void GrowRows(const std::vector<std::vector<char>>& galaxy,std::vector<std::pair<std::size_t,std::size_t>>& galaxies)
    {
        std::set<std::size_t> yCords;
        for(int y = 0; y < galaxy.size();y++)
        {
            if(std::all_of(galaxy[y].begin(),galaxy[y].end(),[&y](char c){return c == '.';}))
            {
                //Find all galaxies bellow and +1mil
                yCords.emplace(y);
            }
        }
        auto ogGalaxies = galaxies;
        for(int i = 0; i < ogGalaxies.size();++i)
        {
            std::size_t count = std::count_if(yCords.begin(),yCords.end(),[&](std::size_t yCord){
                return yCord < ogGalaxies[i].first;
            });
            if(count > 0)
                galaxies[i].first += (GROW_SIZE * count) - count;
        }
    }
    void GrowCol(const std::vector<std::vector<char>>& galaxy, std::vector<std::pair<std::size_t,std::size_t>>& galaxies)
    {
        std::set<std::size_t> xCoords;
        for(int x = 0; x < galaxy[0].size();x++)
        {
            bool blank {true};
            for(int y = 0; y < galaxy.size();y++)
            {
                if(galaxy[y][x] != '.')
                {
                    blank = false;
                    break;
                }
            }
            if(blank)
            {
                xCoords.emplace(x);
            }
        }
        auto ogGalaxies = galaxies;
        for(int i = 0; i < ogGalaxies.size();++i)
        {
            std::size_t count = std::count_if(xCoords.begin(),xCoords.end(),[&](std::size_t xCord){
                return xCord < ogGalaxies[i].second;
            });
            if(count > 0)
                galaxies[i].second += (GROW_SIZE * count) - count;
        }
    }
    void FindGalaxies(const std::vector<std::vector<char>>& galaxy, std::vector<std::pair<std::size_t,std::size_t>>& galaxies)
    {
        for(int y = 0;y < galaxy.size();y++) 
        {
            bool blank {true};
            for(int x = 0; x < galaxy[y].size();x++)
            {
                if(galaxy[y][x ] == '#')
                    galaxies.push_back({y,x});
            }
        }
        
    }
    std::size_t CalculateDistance(const std::vector<std::vector<char>>& galaxy, const std::vector<std::pair<std::size_t,std::size_t>>& galaxies)
    {
        std::size_t sum {0};
        for(std::size_t i = 0; i < galaxies.size()-1;++i)
        {
            for(std::size_t g = i+1; g < galaxies.size();++g)
            {
                std::pair<std::size_t,std::size_t> referenceGalaxy = galaxies[i];
                std::pair<std::size_t,std::size_t> measuredGalaxy = galaxies[g];
                int yDist = std::abs(static_cast<int>(measuredGalaxy.first - referenceGalaxy.first));
                int xDist = std::abs(static_cast<int>(measuredGalaxy.second - referenceGalaxy.second));
                int totalDist = yDist + xDist;
                // std::cout << i+1 << " <-> " << g+1 << " " << totalDist << '\n';
                sum += totalDist;
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
    std::size_t sum {0};
    FindGalaxies(graph,galaxies);
    GrowRows(graph,galaxies);
    GrowCol(graph,galaxies);
    return CalculateDistance(graph,galaxies);
}

namespace Part2
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        char c;
        istream >>  c;
        std::vector<char> row;
        while(istream)
        {
            row.push_back(c);
            istream >> c;
        }
        work.graph.push_back(row);
        return istream;
    }
}