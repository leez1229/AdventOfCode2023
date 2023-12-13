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

int Part1::Work::Output()
{
    return winningCardTotals;
}


namespace Part1
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        std::string card;
        istream >> card;
        istream >> card;
        std::string number;
        istream >> number;
        std::set<int> winningNumbers;
        while(istream && number != "|")
        {
            winningNumbers.emplace(std::atoi(number.c_str()));
            istream >> number;
        }
        int winnings = 0;
        istream >> number;
        while(istream)
        {
            if(winningNumbers.count(std::atoi(number.c_str())))
            {
                if(winnings == 0)
                    winnings = 1;
                else
                    winnings *= 2;
            }
            istream >> number;
        }
        work.winningCardTotals += winnings;
        return istream;
    }
}