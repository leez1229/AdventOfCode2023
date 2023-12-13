#include "Part1.h"
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

    bool ValidateBlocks(const std::pair<std::string,int> blockPickCount)
    {
        std::string blockColor = blockPickCount.first;
        int blockCount =  blockPickCount.second;
        if(blockColor == "red" && blockCount > MAX_RED)
            return false;
        else if(blockColor == "blue" && blockCount > MAX_BLUE)
            return false;
        else if(blockColor == "green" && blockCount > MAX_GREEN)
            return false;
        return true;
    }
}

Part1::Part1()
{
}

int Part1::Output()
{
    int sum{0};
    std::for_each(possibleGames.begin(),possibleGames.end(),[&sum](int n){
        sum += n;
    });
    return sum;
}

std::istream& operator>>(std::istream& istream, Part1& part)
{
    std::string gameNumStr;
    istream >> gameNumStr;
    istream >> gameNumStr;
    gameNumStr = gameNumStr.substr(0,gameNumStr.size()-1);
    auto blocks = ParseBlocks(istream);
    if(std::all_of(blocks.begin(),blocks.end(),ValidateBlocks))
    {
        part.possibleGames.push_back(std::atoi(gameNumStr.c_str()));
    }
    return istream;
}