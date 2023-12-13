#include "Part2.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    
}

Part2::Work::Work(std::map<std::string,std::vector<std::pair<std::vector<int>,std::size_t>>>& cache)
:cache(cache)
{}

std::size_t Part2::Work::Output()
{
    return MoveSprings(input,groups);
}

std::size_t Part2::Work::MoveSprings(const std::string& str,std::vector<int> groups)
{
    std::size_t value;
    if(CheckCache(str,groups,value))
    {
        return value;
    }

    if(str.size() == 0)
    {
        if(groups.empty())
            return 1;
        return 0;
    }
    if(str.at(0) == '.')
        return Cache(str,groups,MoveSprings(str.substr(1),groups));
    if(str.at(0) == '?')
    {
        std::string tempStringOne = str;
        std::string tempStringTwo = str;
        return Cache(str,groups,MoveSprings(tempStringOne.replace(0,1,"."),groups) + MoveSprings(tempStringTwo.replace(0,1,"#"),groups));
    }
    else if(str.at(0) == '#')
    {
        if(groups.empty())
            return Cache(str,groups,0);
        if(str.size() < groups[0])
            return Cache(str,groups,0);
        if(str.substr(0,groups[0]).find('.') != std::string::npos)
            return Cache(str,groups,0);
        if(groups.size() > 1)
        {
            if(str.size() < groups[0] + 1 || str.at(groups[0]) == '#')
                return Cache(str,groups,0);
            return Cache(str,groups,MoveSprings(str.substr(groups[0]+1),std::vector<int>{groups.begin()+1,groups.end()}));
        }
        else
            return Cache(str,groups,MoveSprings(str.substr(groups[0]),{}));
    }
    throw std::logic_error("Bad Logic");
}


bool Part2::Work::CheckCache(const std::string& str, std::vector<int> groups, std::size_t& value)
{
    auto it = cache.find(str);
    if(it != cache.end())
    {
        auto& cachedGroups = it->second;
        for(auto& groupPair: cachedGroups)
        {
            if(groupPair.first.size() == groups.size() && std::equal(groupPair.first.begin(),groupPair.first.end(),groups.begin()))
            {
                // std::cout << "Cache hit " << str << " " << groupPair.second << '\n';
                value = groupPair.second;
                return true;
            }
        }
    }
    return false;
}

std::size_t Part2::Work::Cache(const std::string& str, std::vector<int> groups, std::size_t value)
{
    auto& cachedGroups = cache[str];
    cachedGroups.push_back({groups,value});
    return value;
}

namespace Part2
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        std::string input;
        istream >> input;
        std::string tempInput = input;

        std::string groupList;
        istream >> groupList;
        std::string tempGroupList = groupList;

        for(int i = 0; i < 5-1;++i)
        {
            input += "?" + tempInput;
            groupList += "," + tempGroupList;
        }
        work.input = input;
        
        std::vector<std::string> split = Split(groupList,',');
        for(std::string& s: split)
        {
            work.groups.push_back(std::atoi(s.c_str()));
        }
        return istream;
    }
}