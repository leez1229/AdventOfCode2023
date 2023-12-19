#include "Part2.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    std::size_t Run(std::string workflow,std::map<std::string,Part2::WorkFlow>& workFlows, std::map<std::string,std::pair<std::size_t,std::size_t>> xmas)
    {
        
        if(workflow == "A")
        {
            std::size_t x = xmas["x"].second - xmas["x"].first + 1;
            std::size_t m = xmas["m"].second - xmas["m"].first + 1;
            std::size_t a = xmas["a"].second - xmas["a"].first + 1;
            std::size_t s = xmas["s"].second - xmas["s"].first + 1;
            return x*m*a*s;
        }
        else if(workflow == "R")
            return 0;

        std::size_t sum {0};
        Part2::WorkFlow& flow = workFlows[workflow];
        for(auto& rule: flow.rules)
        {
            if(rule.id.empty())
            {
                sum += Run(rule.gotoWorkFlow,workFlows,xmas);
            }
            else if(rule.lessThan && rule.value > xmas[rule.id].first)
            {
                if(xmas[rule.id].second >= rule.value)
                {
                    auto tempXmas = xmas;
                    auto& pair = tempXmas[rule.id];
                    pair.second = rule.value - 1;

                    xmas[rule.id].first = rule.value;
                    sum += Run(rule.gotoWorkFlow,workFlows,tempXmas);
                }
                else
                {
                    return sum += Run(rule.gotoWorkFlow,workFlows,xmas);
                }
            }
            else if(!rule.lessThan && rule.value < xmas[rule.id].second)
            {
                if(xmas[rule.id].first <= rule.value)
                {
                    auto tempXmas = xmas;
                    auto& pair = tempXmas[rule.id];
                    pair.first = rule.value + 1;

                    xmas[rule.id].second = rule.value;
                    sum += Run(rule.gotoWorkFlow,workFlows,tempXmas);
                }
                else
                {
                    return sum += Run(rule.gotoWorkFlow,workFlows,xmas);
                }
            }
        }
        return sum;
    }
}

Part2::Work::Work()
{
}

std::size_t Part2::Work::Output()
{
    std::size_t sum {0};
    WorkFlow accept;
    accept.rules.push_back({[&sum](std::string,long long int){
        return true;
    },""});

    WorkFlow reject;
    reject.rules.push_back({[](std::string,long long int){
        return true;
    },""});

    workFlows["A"] = accept;
    workFlows["R"] = reject;

    const std::array<std::string,4> xmas = {"x","m","a","s"};
    std::map<std::string,std::pair<std::size_t,std::size_t>> xmasMap;
    xmasMap["x"] = {1,4000};
    xmasMap["m"] = {1,4000};
    xmasMap["a"] = {1,4000};
    xmasMap["s"] = {1,4000};

    return Run("in",workFlows,xmasMap);
   
    //256000000000000 - MAX
    //167409079868000
    return 0;
}

namespace Part2
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        std::string input;
        istream >> input;
        input = input.substr(0,input.size()-1);
        
        std::vector<std::string> split1 = Split(input,'{');
        std::string workflow = split1[0];
        WorkFlow flow;
        std::vector<std::string> split2 = Split(split1[1],',');
        for(int i = 0; i < split2.size();++i)
        {
            if(i == split2.size()-1)
            {
                decltype(flow.rules)::value_type rule = {[](std::string,long long int){return true;},split2[i],0};
                flow.rules.push_back(rule);
            }
            else
            {
                std::vector<std::string> split3  = Split(split2[i],':');
                std::string goToFlow = split3.back();
                std::vector<std::string> split4 = Split(split3.front(),'>');
                if(split4.size() == 1)
                {
                    split4 = Split(split3.front(),'<');
                    int v = std::stoi(split4.back());
                    std::string t = split4.front();
                    flow.rules.push_back({[t,v](std::string toy, long long int val){
                        if(toy == t)
                        {
                            return val < v;
                        }
                        return false;
                    },
                    goToFlow,
                    v,
                    true,
                    t
                    });
                }
                else
                {
                    int v = std::stoi(split4.back());
                    std::string t = split4.front();
                    flow.rules.push_back({[t,v](std::string toy, long long int val){
                        if(toy == t)
                        {
                            return val > v;
                        }
                        return false;
                    },
                    goToFlow,
                    v,
                    false,
                    t
                    });
                }
            }
        }
        work.workFlows[workflow] = flow;
        return istream;
    }
}