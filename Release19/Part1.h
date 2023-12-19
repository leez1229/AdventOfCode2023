#pragma once

#include <stack>
#include <istream>
#include <map>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>
#include <set>
#include <array>
#include <queue>
#include <functional>

namespace Part1
{
    struct Toy
    {
        std::vector<std::pair<std::string,int>> desc;
    };
    
    struct WorkFlow
    {
        std::vector<std::pair<std::function<bool(std::string, int,Toy&)>,std::string>> rules;
    };
    
   
    class Work
    {
    public:
        Work();
        std::size_t Output();
        friend std::istream& operator>>(std::istream& istream, Part1::Work& work);
    private:
        std::map<std::string,WorkFlow> workFlows;
        std::vector<Toy> toys;
        bool readingRules {true};
    };
}