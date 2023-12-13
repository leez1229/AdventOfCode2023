#include "Part2.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>

namespace
{
    const int MAX_RED = 12;
    const int MAX_GREEN = 13;
    const int MAX_BLUE = 14;

    std::string Sanitize(const std::string& str)
    {
        std::string sanatizedStr = str;
        auto commaPos = sanatizedStr.find(',');
        if(commaPos != std::string::npos)
        {
            sanatizedStr = sanatizedStr.erase(commaPos);
        }
        auto semi = sanatizedStr.find(';');
        if(semi != std::string::npos)
        {
            sanatizedStr = sanatizedStr.erase(semi);
        }
        return sanatizedStr;
    }

    std::vector<std::pair<std::string,int>> ParseBlocks(std::istream& istream)
    {
        std::vector<std::pair<std::string,int>>  pickedBlocks;
        while(istream)
        {
            int pickCount;
            istream >> pickCount;
            std::string color;
            istream >> color;
            color = Sanitize(color);
            pickedBlocks.push_back({color,pickCount});
        }
        return pickedBlocks;
    }

    std::array<int,3> ValidateBlocks(const std::vector<std::pair<std::string,int>> blockPickCount)
    {
        int currentMaxRed{0};
        int currentMaxGreen{0};
        int currentMaxBlue{0};
        std::for_each(blockPickCount.begin(),blockPickCount.end(),[&](std::pair<std::string,int> blockChoice){
            std::string blockColor = blockChoice.first;
            int blockCount =  blockChoice.second;
            if(blockColor == "red" && blockCount > currentMaxRed)
                currentMaxRed = blockCount;
            else if(blockColor == "blue" && blockCount > currentMaxBlue)
                currentMaxBlue = blockCount;
            else if(blockColor == "green" && blockCount > currentMaxGreen)
                currentMaxGreen = blockCount;
        });
        
        return {currentMaxRed,currentMaxGreen,currentMaxBlue};
    }
}

Part2::Part2()
{
}

int Part2::Output()
{
    int sum{0};
    std::for_each(possibleGames.begin(),possibleGames.end(),[&sum](const std::array<int,3>& colorCount){
        int power = colorCount[0] * colorCount[1] * colorCount[2];
        sum += power;
    });
    return sum;
}

std::istream& operator>>(std::istream& istream, Part2& part)
{
    std::string gameNumStr;
    istream >> gameNumStr;
    istream >> gameNumStr;
    gameNumStr = gameNumStr.substr(0,gameNumStr.size()-1);
    auto blocks = ParseBlocks(istream);
    auto leastBlockCount = ValidateBlocks(blocks);
    part.possibleGames.push_back(leastBlockCount);
    return istream;
}