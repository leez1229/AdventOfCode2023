#include "Part2.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    const std::map<const char*,int> ALPHA_VALUES = {{"zero",0},{"one",1},{"two",2},{"three",3},{"four",4},{"five",5},{"six",6},{"seven",7},{"eight",8},{"nine",9}};
    std::pair<std::size_t,int> CheckForFirstAlphaNumber(const std::string& str)
    {
        std::pair<std::size_t,int> currentAlphaValue {std::string::npos,-1};
        std::for_each(ALPHA_VALUES.begin(),ALPHA_VALUES.end(),[&](auto p){
            std::size_t pos = str.find(p.first);
            if(pos != std::string::npos && pos < currentAlphaValue.first)
            {
                currentAlphaValue = {pos,p.second};
            }
        });
        return currentAlphaValue;
    }
    std::pair<std::size_t,int> CheckForLastAlphaNumber(const std::string& str)
    {
        std::pair<std::size_t,int> currentAlphaValue {std::string::npos,-1};
        std::for_each(ALPHA_VALUES.begin(),ALPHA_VALUES.end(),[&](auto p){
            std::size_t pos = str.rfind(p.first);
            if(pos != std::string::npos && (pos > currentAlphaValue.first || currentAlphaValue.first == std::string::npos))
            {
                currentAlphaValue = {pos,p.second};
            }
        });
        return currentAlphaValue;
    }
}

Part2::Part2()
{
}

int Part2::Output()
{
    int sum{0};
    std::for_each(numbers.begin(),numbers.end(),[&sum](int n){
        sum += n;
    });
    return sum;
}

std::istream& operator>>(std::istream& istream, Part2& part2)
{
    std::string input;
    istream >> input;
    std::size_t digitIndex = 0;
    auto firstDigit = std::find_if(input.begin(),input.end(),[&digitIndex](const char& s){
        if(std::isdigit(s))
        {
            return true;
        }
        digitIndex++;
        return false;
    });
    std::string firstStringDigit;
    if(firstDigit != input.end())
        firstStringDigit = (*firstDigit);
    std::pair<std::size_t,int> firstAlpha = CheckForFirstAlphaNumber(input);
    if(firstAlpha.first < digitIndex)
    {
        firstStringDigit = std::to_string(firstAlpha.second);
    }

    digitIndex = input.size();
    auto lastDigit = std::find_if(input.rbegin(),input.rend(),[&digitIndex](const char& s){
        digitIndex--;
        if(std::isdigit(s))
        {
            return true;
        }
        return false;
    });
    std::string lastStringDigit;
    if(lastDigit != input.rend())
        lastStringDigit = (*lastDigit);
    std::pair<std::size_t,int> lastAlpha = CheckForLastAlphaNumber(input);
    if(lastAlpha.first != std::string::npos && lastAlpha.first > digitIndex)
    {
        lastStringDigit = std::to_string(lastAlpha.second);
    }

    std::string combinedDigit = firstStringDigit + lastStringDigit;
    std::cout << combinedDigit << '\n';
    part2.numbers.push_back(atoi(combinedDigit.c_str()));
    return istream;
}