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

std::size_t Part1::Work::Output()
{
    std::size_t sum {0};
    WorkFlow accept;
    accept.rules.push_back({[&sum](std::string,int,Toy& t){
        for(auto& tVal: t.desc)
        {
            sum += tVal.second;
        }
        return true;
    },""});

    WorkFlow reject;
    reject.rules.push_back({[](std::string,int,Toy&){
        return true;
    },""});

    workFlows["A"] = accept;
    workFlows["R"] = reject;

    for(auto& toy: toys)
    {
        //std::string toyDesc = toy.first;
        //int toyValue = toy.second;
        std::string gotoFlow = "in";
        while(!gotoFlow.empty())
        {
            auto& workFlow = workFlows[gotoFlow];
            for(auto& rule: workFlow.rules)
            {
                auto it = std::find_if(toy.desc.begin(),toy.desc.end(),[&rule,&toy](auto& pair){
                    return rule.first(pair.first,pair.second,toy);
                });

                if(it != toy.desc.end())
                {
                    gotoFlow = rule.second;
                    break;
                }
            }
        }
    }
    return sum;
}

namespace Part1
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        std::string input;
        istream >> input;
        input = input.substr(0,input.size()-1);
        if(!input.empty() && work.readingRules)
        {
            std::vector<std::string> split1 = Split(input,'{');
            std::string workflow = split1[0];
            WorkFlow flow;
            std::vector<std::string> split2 = Split(split1[1],',');
            for(int i = 0; i < split2.size();++i)
            {
                if(i == split2.size()-1)
                {
                    decltype(flow.rules)::value_type rule = {[](std::string,int,Toy&){return true;},split2[i]};
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
                        flow.rules.push_back({[t = split4.front(),v = std::stoi(split4.back())](std::string toy, int val,Toy&){
                            if(toy == t)
                            {
                                return val < v;
                            }
                            return false;
                        },
                        goToFlow
                        });
                    }
                    else
                    {
                        flow.rules.push_back({[t = split4.front(),v = std::stoi(split4.back())](std::string toy, int val,Toy&){
                            if(toy == t)
                            {
                                return val > v;
                            }
                            return false;
                        },
                        goToFlow
                        });
                    }
                }
            }
            work.workFlows[workflow] = flow;
        }
        else if(!input.empty() && !work.readingRules)
        {
            std::string sanatizedToyInput = input.substr(1,input.size()-1);
            std::vector<std::string> toys = Split(sanatizedToyInput,',');
            Toy t;
            for(auto& toy: toys)
            {
                std::vector<std::string> toyValue = Split(toy,'=');
                t.desc.push_back({toyValue.front(),std::stoi(toyValue.back())});
            }
            work.toys.push_back(t);
        }
        else
        {
            work.readingRules = false;
        }
        
        return istream;
    }
}