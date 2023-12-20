#include "Part2.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
   
}

std::queue<Part2::Module*> Part2::Module::modulesToProcess;
std::size_t Part2::Module::sendLow = 0;
std::size_t Part2::Module:: sendHigh = 0;

Part2::Work::Work()
{
}


std::size_t Part2::Work::Output()
{
    Module& broadcaster = moduleMapper["broadcaster"];
    std::size_t hb1 {0};
    std::size_t hb2 {0};
    std::size_t hb3 {0};
    std::size_t hb4 {0};
    std::size_t i = 0;
    while(true)
    {
        i++;
        for(Module* m: broadcaster.outputModules)
        {
            Module::sendLow++;
            m->inputs.push(&broadcaster);
            Module::modulesToProcess.push(m);
        }
        while(!Module::modulesToProcess.empty())
        {
            Module* proc = Module::modulesToProcess.front();
            if(proc->id == "hb")
            {
                if(proc->inputs.front()->currentState && proc->inputs.front()->id == "js")
                    hb1 = i;
                else if(proc->inputs.front()->currentState && proc->inputs.front()->id == "zb")
                    hb2 = i;
                else if(proc->inputs.front()->currentState && proc->inputs.front()->id == "bs")
                    hb3 = i;
                else if(proc->inputs.front()->currentState && proc->inputs.front()->id == "rr")
                    hb4 = i;
            }
            if(hb1 != 0 && hb2 != 0 && hb3 != 0 && hb4 != 0)
            {
                std::cout << "JS: "  << hb1 << '\n';
                std::cout << "ZB: "  << hb2 << '\n';
                std::cout << "BS: "  << hb3 << '\n';
                std::cout << "RR: "  << hb4 << '\n';
                std::size_t result = LCM(hb1,hb2);
                result = LCM(hb3,result);
                result = LCM(hb4,result);
                return result;
            }
            if(proc->id == "rx")//For memory cleanup since no types dont send so they just collect
                proc->inputs.pop();

            Module::modulesToProcess.pop();
            proc->ProcessInput();
        }
    }
    return 0;
}

namespace Part2
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        std::string input;
        istream >> input;
        std::string arrow;
        istream >> arrow;
        char moduleType;
        bool isBroadcaster = true;
        if(input != "broadcaster")
        {
            isBroadcaster = false;
            moduleType = input.front();
            input = input.substr(1);
        }
        Module& rootModule = work.moduleMapper[input];
        rootModule.id = input;
        std::string moduleName;
        istream >>  moduleName;
        while(istream)
        {
            if(moduleName.back() == ',')
                moduleName = moduleName.substr(0,moduleName.size()-1);
            Module& m = work.moduleMapper[moduleName];
            m.id = moduleName;
            m.inputModuleStates[&rootModule] = rootModule.currentState;
            rootModule.outputModules.push_back(&m);
            istream >> moduleName;
        }
        if(!isBroadcaster)
        {
            if(moduleType == '%')
            {
                rootModule.send = [&rootModule](){
                    bool input = rootModule.inputs.front()->currentState;
                    rootModule.inputs.pop();
                    if(!input)
                    {
                        bool newState = !rootModule.currentState;
                        rootModule.currentState = newState;
                        return true;
                    }
                    return false;
                };
            }
            else if(moduleType == '&')
            {
                rootModule.send = [&rootModule](){
                    Module* input = rootModule.inputs.front();
                    rootModule.inputs.pop();
                    rootModule.inputModuleStates[input] = input->currentState;

                    bool isAllTrue {true};
                    for(auto& p: rootModule.inputModuleStates)
                    {
                        if(!p.second)
                        {
                            isAllTrue = false;
                            break;
                        }
                    }
                    rootModule.currentState = !isAllTrue;
                    return true;
                };
            }
        }
        return istream;
    }
}