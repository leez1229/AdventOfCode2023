#include "Part3.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    std::size_t DetermineWinnings(const std::set<int>& winners, const std::vector<int> ownedNumbers)
    {
        return std::count_if(ownedNumbers.begin(),ownedNumbers.end(),[&winners](int number){
            return winners.count(number);
        });
    }
}

Part3::Work::Work()
{
}

//Create a heuristic where you can determine how many coppies each card makes then just add up that way
std::size_t Part3::Work::Output()
{
    for(std::size_t i = 0; i < invetory.size(); i++)
    {
        std::size_t count = DetermineWinnings(invetory[i].first,invetory[i].second);
        heuristicCopies[i] = count + 1;
        copiesCreated.push_back(i);
        for(std::size_t j = i + 1; j <= i + count; j++)
        {
            copiesCreated[j]++;
        }
    }
    ProcessQueue();
    return processedCards;
}

void Part3::Work::ProcessQueue()
{
    for(int i = 0; i < multiplier.size(); i++)
    {
        processedCards += heuristicCopies[i] * multiplier[i];
        //5*1
        //5
        //3*2
        //11
        //3*3
        //20
        //5*1
        //28
        //5*1
        //32
        
    }
}

namespace Part3
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        std::string card;
        istream >> card;
        istream >> card;
        std::string number;
        istream >> number;
        decltype(work.invetory)::value_type scratchers;
        while(istream && number != "|")
        {
            scratchers.first.emplace(std::atoi(number.c_str()));
            istream >> number;
        }
        istream >> number;
        while(istream)
        {
            scratchers.second.push_back(std::atoi(number.c_str()));
            istream >> number;
        }
        work.invetory.push_back(scratchers);
        return istream;
    }
}