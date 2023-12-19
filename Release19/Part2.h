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

namespace Part2
{
    struct Toy
    {
        std::vector<std::pair<std::string,long long int>> desc;
    };
    struct Rule
    {
        std::function<bool(std::string, long long int)> rule;
        std::string gotoWorkFlow;
        int value;
        bool lessThan;
        std::string id;
    };
    struct WorkFlow
    {
        std::vector<Rule> rules;
    };
    
   
    class Work
    {
    public:
        Work();
        std::size_t Output();
        friend std::istream& operator>>(std::istream& istream, Part2::Work& work);
    private:
        std::map<std::string,WorkFlow> workFlows;
        std::vector<Toy> toys;
        bool readingRules {true};
    };
}