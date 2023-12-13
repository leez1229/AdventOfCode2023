#include "Part2.h"
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

Part2::Work::Work()
{
}

//Create a heuristic where you can determine how many coppies each card makes then just add up that way
std::size_t Part2::Work::Output()
{
    for(int i = 0; i < invetory.size(); i++)
    {
        processedCards++;
        std::size_t count = DetermineWinnings(invetory[i].first,invetory[i].second);
        WinningCard(i,count);
    }
    ProcessQueue();
    return processedCards;
}

void Part2::Work::ProcessQueue()
{
    while(!winingScratcherQueue.empty())
    {
        processedCards++;
        std::size_t copiedCardIndex = winingScratcherQueue.front();
        winingScratcherQueue.pop();
        std::size_t count = DetermineWinnings(invetory[copiedCardIndex].first,invetory[copiedCardIndex].second);
        WinningCard(copiedCardIndex,count);
    }
}

void Part2::Work::WinningCard(std::size_t winningCardIndex, std::size_t matchingNumbers)
{
    for(std::size_t c = winningCardIndex + 1; c <= winningCardIndex + matchingNumbers; ++c)
    {
        winingScratcherQueue.push(c);
    }
}

namespace Part2
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