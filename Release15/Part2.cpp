#include "Part2.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    int CalculateHash(const Part2::Lense& lense)
    {
        int currentValue = 0;
        for(char c: lense.label)
        {
            currentValue += c;
            currentValue *= 17;
            currentValue %= 256;
        }
        return currentValue;
    }
}

Part2::Work::Work()
{
}

std::size_t Part2::Work::Output()
{
    std::size_t sum{0};
    for(auto& lense: input)
    {
        PerformOperation(lense);
    }
    for(int i = 0; i < boxes.size();++i)
    {
        for(int j = 0;j < boxes[i].size();++j)
        {
            sum += (i+1) * (j+1) * std::next(boxes[i].begin(),j)->val;
        }
    }
    return sum;
}

void Part2::Work::PerformOperation(const Part2::Lense& l)
{
    int box = CalculateHash(l);
    std::list<Lense>& lenses = boxes[box];
    auto lenseEqual = [&l](const Lense& boxLense){
                            return l.label == boxLense.label;
                        };
    if(l.operation == '-')
    {
        lenses.remove_if(lenseEqual);
    }
    else
    {
        auto it = std::find_if(lenses.begin(),lenses.end(),lenseEqual);
        if(it != lenses.end())
            it->val = l.val;
        else
            lenses.push_back(l);
    }
}
namespace Part2
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        std::string input;
        istream >> input;
        std::vector<std::string> split = Split(input,',');
        for(std::string s: split)
        {
            std::size_t pos = s.find('=');
            Lense l;
            if(pos != std::string::npos)
            {
                l.operation = '=';
                l.val = std::atoi(s.substr(pos+1).c_str());
                l.label = s.substr(0,pos);
            }
            else
            {
                l.operation = '-';
                l.label = s.substr(0,s.size()-1);
            }
            work.input.push_back(l);
        }
        return istream;
    }
}