#include "Part1.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
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
    void GrowRows(std::vector<std::vector<char>>& galaxy)
    {
        for(int y = 0; y < galaxy.size();y++)
        {
            if(std::all_of(galaxy[y].begin(),galaxy[y].end(),[&y](char c){return c == '.';}))
            {
                galaxy.insert(std::next(galaxy.begin(),y),galaxy[y]);
                ++y;
            }
        }
    }
    void GrowCol(std::vector<std::vector<char>>& galaxy)
    {
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
                for(int z = 0; z < galaxy.size();z++)
                {
                    std::vector<char>& row = galaxy[z];
                    row.insert(std::next(row.begin(),x),'.');
                }
                ++x;
            }
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

Part1::Work::Work()
{
}

std::size_t Part1::Work::Output()
{
    std::size_t sum {0};
    GrowRows(graph);
    GrowCol(graph);
    FindGalaxies(graph,galaxies);
    return CalculateDistance(graph,galaxies);
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
            row.push_back(c);
            istream >> c;
        }
        work.graph.push_back(row);
        return istream;
    }
}