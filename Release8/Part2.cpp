#include "Part2.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>
#include <queue>

namespace
{
   bool EndInZ(const std::string& p)
   {
        return p.back() == 'Z';
   }

   std::size_t GCF(std::size_t a, std::size_t b)
   {
        if(a > b)
        {
            std::size_t temp = a;
            a = b;
            b = temp;
        }
        std::size_t gcf {0};
        for(std::size_t i = 1; i < a; i++)
        {
            if(a % i == 0 && b % i == 0)
            {
                gcf = i;
            }
        }
        return gcf;
   }

   std::size_t LCM(std::size_t a, std::size_t b)
   {
        return a * b / GCF(a,b);
   }
}

Part2::Work::Work()
{
}

std::size_t Part2::Work::Output()
{
   

    //Find all nodes that end in A
    std::vector<std::string> all_positions;
    std::for_each(graph.begin(),graph.end(),[&all_positions](const auto& p){
        std::string start = p.first;
        if(start.back() == 'A')
        {
            all_positions.push_back(start);
        }
    });


    std::size_t sum {0};
    std::size_t index {0};
    std::queue<std::size_t> pathsToZ;
    while(!all_positions.empty())
    {
        for(int i = 0; i < all_positions.size();++i)
        {
            if(EndInZ(all_positions[i]))
            {
                all_positions.erase(std::next(all_positions.begin(),i));
                pathsToZ.push(sum);
            }
        }

        std::for_each(all_positions.begin(),all_positions.end(),[&](std::string& p){
            if(path[index] == 'R')
                p = graph[p].second;
            else
                p = graph[p].first;
        });
        
        index = ++index % path.size();
        ++sum;
    }

    while(pathsToZ.size() > 1)
    {
        std::size_t a = pathsToZ.front();
        pathsToZ.pop();
        std::size_t b = pathsToZ.front();
        pathsToZ.pop();
        pathsToZ.push(LCM(a,b));
    }

    return pathsToZ.front();
}


namespace Part2
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        if(work.path.empty())
        {
            char p;
            istream >> p;
            while(istream)
            {
                work.path.push_back(p);
                istream >> p;
            }
        }
        else
        {
            std::string start;
            istream >> start;
            char garbage;
            istream >> garbage;
            istream >> garbage;
            std::string left;
            istream >> left;
            left = left.substr(0,left.size()-1);
            std::string right;
            istream >> right;
            right = right.substr(0,right.size()-1);
            work.graph[start] = {left,right};
        }

        return istream;
    }
}