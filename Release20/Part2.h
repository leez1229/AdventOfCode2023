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
    struct Module
    {
        static std::queue<Module*> modulesToProcess;
        static std::size_t sendLow;
        static std::size_t sendHigh;
        std::vector<Module*> outputModules;
        std::map<Module*,bool> inputModuleStates;
        std::queue<Module*> inputs;
        std::function<bool()> send;
        std::string id;
        bool currentState{false};

        void ProcessInput()
        {
            if(send && send())
            {
                for(Module* m: outputModules)
                {
                    if(currentState)
                        sendHigh++;
                    else
                        sendLow++;
                    m->inputs.push(this);
                    modulesToProcess.push(m);
                }
            }
        }
        
    };

    class Work
    {
    public:
        Work();
        std::size_t Output();
        friend std::istream& operator>>(std::istream& istream, Part2::Work& work);
    private:
        std::map<std::string,Module> moduleMapper;
        
        // std::map<std::string,std::vector<std::string>> mapInputToModules;
    };
}