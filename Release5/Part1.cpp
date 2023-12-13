#include "Part1.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    std::size_t FindLocation(const ::Part1::Mapper& start,std::size_t value)
    {
        std::size_t mappedValue = value;
        auto it = std::find_if(start.lines.begin(),start.lines.end(),[&value](const std::array<std::size_t,3>& values){
            return values[1] <= value && values[1] + values[2] >= value;
        });
        
        if(it != start.lines.end())
        {
            mappedValue = (value - it->at(1)) + it->at(0);
        }

        if(!start.linkedMap)
            return mappedValue;

        return FindLocation(*(start.linkedMap),mappedValue);
    }
}

Part1::Work::Work()
{
}

std::size_t Part1::Work::Output()
{
    std::cout << "Working on Output";
    std::vector<std::size_t> locations;
    std::for_each(seeds.begin(),seeds.end(),[&](std::size_t seed){
        locations.push_back(FindLocation(almanac["seed"],seed));
    });
    return *(std::min_element(locations.begin(),locations.end()));
}


namespace Part1
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        std::string name;
        istream >> name;
        if(name == "seeds:")
        {
            std::cout << "Working on Seeds\n";
            std::string seed;
            istream >> seed;
            while(istream && seed != ".")
            {
                work.seeds.push_back(std::atoll(seed.c_str()));
                istream >> seed;
            }
        }
        else
        {
            if(name.find('-') != std::string::npos)
            {
                std::cout << "Working on " << name << "\n";
                std::vector<std::string> mapNames = Split(name,'-');
                work.almanac[mapNames[0]].linkedMap = &work.almanac[mapNames[2]];
                work.currentBuildingMapper = &work.almanac[mapNames[2]];
            }
            else
            {
                // std::cout << "Building Range Map\n";
                std::array<std::size_t,3> values;
                std::size_t value;
                value = std::atoll(name.c_str());
                std::size_t i = 0;
                while(istream)
                {
                    values[i++] = value;
                    istream >> value;
                }
                work.currentBuildingMapper->lines.push_back(values);
                // std::size_t min = *(std::min_element(values.begin(),values.begin()+1));
                // values[0] -= min;
                // values[1] -= min;
                // for(std::size_t i = 0; i < values[2];++i)
                // {
                //     work.currentBuildingMapper->rangeMapping[values[1] + i] = std::make_pair(values[0] + i,min);
                // }
            }
        }
    
        return istream;
    }
}