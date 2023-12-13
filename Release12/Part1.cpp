#include "Part1.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    int MoveSprings(const std::string& str,std::vector<int> groups)
    {
        if(str.size() == 0)
        {
            if(groups.empty())
                return 1;
            return 0;
        }
        if(str.at(0) == '.')
            return MoveSprings(str.substr(1),groups);
        if(str.at(0) == '?')
        {
            std::string tempStringOne = str;
            std::string tempStringTwo = str;
            return MoveSprings(tempStringOne.replace(0,1,"."),groups) + MoveSprings(tempStringTwo.replace(0,1,"#"),groups);
        }
        else if(str.at(0) == '#')
        {
            if(groups.empty())
                return 0;
            if(str.size() < groups[0])
                return 0;
            if(str.substr(0,groups[0]).find('.') != std::string::npos)
                return 0;
            if(groups.size() > 1)
            {
                if(str.size() < groups[0] + 1 || str.at(groups[0]) == '#')
                    return 0;
                return MoveSprings(str.substr(groups[0]+1),std::vector<int>{groups.begin()+1,groups.end()});
            }
            else
                return MoveSprings(str.substr(groups[0]),{});
        }
        throw std::logic_error("Bad Logic");
    }
}

Part1::Work::Work()
{
}

std::size_t Part1::Work::Output()
{
    //bool test = ValidateConfiguration("#?#.###",{1,1,3});
    return MoveSprings(input,groups);
}

namespace Part1
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        istream >> work.input;
        std::string groupList;
        istream >> groupList;
        std::vector<std::string> split = Split(groupList,',');
        for(std::string& s: split)
        {
            work.groups.push_back(std::atoi(s.c_str()));
        }
        return istream;
    }
}