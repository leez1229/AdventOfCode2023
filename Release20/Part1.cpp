#include "Part1.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    
}

std::queue<Part1::Module*> Part1::Module::modulesToProcess;
std::size_t Part1::Module::sendLow = 0;
std::size_t Part1::Module:: sendHigh = 0;

Part1::Work::Work()
{
}

std::size_t Part1::Work::Output()
{
    Module& broadcaster = moduleMapper["broadcaster"];
    
    for(int i = 0; i < 1000;++i)
    {
        Module::sendLow++;
        for(Module* m: broadcaster.outputModules)
        {
            Module::sendLow++;
            m->inputs.push(&broadcaster);
            Module::modulesToProcess.push(m);
        }
        while(!Module::modulesToProcess.empty())
        {
            Module* proc = Module::modulesToProcess.front();
            Module::modulesToProcess.pop();
            proc->ProcessInput();
        }
    }
    return Module::sendLow *  Module::sendHigh;
}

namespace Part1
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