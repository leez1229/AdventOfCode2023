#include "Part2.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    std::vector<std::pair<std::size_t,std::size_t>> Transform(const ::Part2::Mapper& start,std::size_t value, std::size_t range)
    {
        std::size_t max = value + range - 1;
        std::size_t min = value;
        std::vector<std::pair<std::size_t,std::size_t>> newRanges;
        auto it = std::find_if(start.lines.begin(),start.lines.end(),[&](const std::array<std::size_t,3>& values){
            std::size_t lineMax = values[1] + values[2] - 1;
            std::size_t lineMin = values[1];
            if(lineMax >= max && max > lineMin && lineMin <= min && min <= lineMax)
            {
                //Full Range is is within
                return true;
            }
            else if(lineMax < max && lineMin <= min && min <= lineMax)
            {
                //Partial Range is in (Range Extends Past)
                return true;
            }
            else if(lineMax >= max && max > lineMin && lineMin > min)
            {
                //Partial Range is in (Range Extends Before)
                return true;
            }
            else if(lineMax < max && lineMin > min)
            {
                //Extends beyond both bounds
                return true;
            }
            return false;
        });
        if(it != start.lines.end())
        {
            auto& values = *it;
            std::size_t lineMax = values[1] + values[2] - 1;
            std::size_t lineMin = values[1];
            if(lineMax >= max && max > lineMin && lineMin <= min && min <= lineMax)
            {
                //Full Range is is within
                // std::cout << "Within Range " << lineMin << " <= " << value << " <= " << lineMax << '\n'; 
                // std::cout << "Transformed Value: " << (value - values[1]) + values[0] << " Range: " << range << '\n';
                newRanges.push_back({((value - values[1]) + values[0]),range});
            }
            else if(lineMax < max && lineMin <= min && min <= lineMax)
            {
                //Partial Range is in (Range Extends Past)
                // std::cout << "Partial Range (Extends Past) " << lineMin << " <= " << value << " <= " << lineMax << '\n'; 
                // std::cout << "Transformed Value: " << (value - values[1]) + values[0] << " Range: " << lineMax - min + 1 << '\n';
                newRanges.push_back({((value - values[1]) + values[0]),lineMax - min + 1});
                //left over range (Right Side)
                std::size_t leftOverRange = max - lineMax;
                std::size_t leftOverStarting = lineMax + 1;
                auto ranges = Transform(start,leftOverStarting,leftOverRange);
                std::copy(ranges.begin(),ranges.end(),std::back_inserter(newRanges));
            }
            else if(lineMax >= max && max > lineMin && lineMin > min)
            {
                //Partial Range is in (Range Extends Before)
                // std::cout << "Partial Range (Extends Before)" << lineMin << " <= " << value << " <= " << lineMax << '\n'; 
                // std::cout << "Transformed Value: " << values[0] << " Range: " << range - (values[1] - min)  << '\n';
                newRanges.push_back({values[0],range - (values[1] - min)});
                //left over range (Left Side)
                std::size_t leftOverRange = (values[1] - min);
                std::size_t leftOverStarting = min;
                auto ranges = Transform(start,leftOverStarting,leftOverRange);
                std::copy(ranges.begin(),ranges.end(),std::back_inserter(newRanges));
            }
            else if(lineMax < max && lineMin > min)
            {
                //Extends beyond both bounds
                // std::cout << "Extends beyond " << lineMin << " <= " << value << " <= " << lineMax << '\n'; 
                // std::cout << "Transformed Value: " << values[0] << " Range: " << values[2] << '\n';
                newRanges.push_back({values[0],values[2]});
                //left over range (Right Side)
                std::size_t leftOverRange = max - lineMax;
                std::size_t leftOverStarting = lineMax + 1;
                auto ranges = Transform(start,leftOverStarting,leftOverRange);
                std::copy(ranges.begin(),ranges.end(),std::back_inserter(newRanges));
                //left over range (Left Side)
                leftOverRange = (values[1] - min);
                leftOverStarting = min;
                ranges = Transform(start,leftOverStarting,leftOverRange);
                std::copy(ranges.begin(),ranges.end(),std::back_inserter(newRanges));
            }
        }
        else
        {
            //Not found
            // std::cout << "Not Found " << value << " Range: " << range << '\n'; 
            newRanges.push_back({value,range});
        }
        return newRanges;
    }
}

Part2::Work::Work()
{
}

std::size_t Part2::Work::Output()
{
    std::vector<std::pair<std::size_t,std::size_t>> transformedSeeds;
    std::for_each(seeds.begin(),seeds.end(),[&](const std::pair<std::size_t,std::size_t>& seed){
        auto ranges = Transform(almanac["soil"],seed.first,seed.second);
        std::copy(ranges.begin(),ranges.end(),std::back_inserter(transformedSeeds));
    });

    auto tempSeeds = transformedSeeds;
    transformedSeeds.clear();
    std::for_each(tempSeeds.begin(),tempSeeds.end(),[&](const std::pair<std::size_t,std::size_t>& seed){
        auto ranges = Transform(almanac["fertilizer"],seed.first,seed.second);
        std::copy(ranges.begin(),ranges.end(),std::back_inserter(transformedSeeds));
    });

    tempSeeds = transformedSeeds;
    transformedSeeds.clear();
    std::for_each(tempSeeds.begin(),tempSeeds.end(),[&](const std::pair<std::size_t,std::size_t>& seed){
        auto ranges = Transform(almanac["water"],seed.first,seed.second);
        std::copy(ranges.begin(),ranges.end(),std::back_inserter(transformedSeeds));
    });

    tempSeeds = transformedSeeds;
    transformedSeeds.clear();
    std::for_each(tempSeeds.begin(),tempSeeds.end(),[&](const std::pair<std::size_t,std::size_t>& seed){
        auto ranges = Transform(almanac["light"],seed.first,seed.second);
        std::copy(ranges.begin(),ranges.end(),std::back_inserter(transformedSeeds));
    });

    tempSeeds = transformedSeeds;
    transformedSeeds.clear();
    std::for_each(tempSeeds.begin(),tempSeeds.end(),[&](const std::pair<std::size_t,std::size_t>& seed){
        auto ranges = Transform(almanac["temperature"],seed.first,seed.second);
        std::copy(ranges.begin(),ranges.end(),std::back_inserter(transformedSeeds));
    });

    tempSeeds = transformedSeeds;
    transformedSeeds.clear();
    std::for_each(tempSeeds.begin(),tempSeeds.end(),[&](const std::pair<std::size_t,std::size_t>& seed){
        auto ranges = Transform(almanac["humidity"],seed.first,seed.second);
        std::copy(ranges.begin(),ranges.end(),std::back_inserter(transformedSeeds));
    });

    tempSeeds = transformedSeeds;
    transformedSeeds.clear();
    std::for_each(tempSeeds.begin(),tempSeeds.end(),[&](const std::pair<std::size_t,std::size_t>& seed){
        auto ranges = Transform(almanac["location"],seed.first,seed.second);
        std::copy(ranges.begin(),ranges.end(),std::back_inserter(transformedSeeds));
    });
    
    std::size_t bsum{0};
    for(auto& s : seeds)
    {
        bsum += s.second;
    }
    std::size_t esum {0};
    for(auto& s : transformedSeeds)
    {
        esum += s.second;
    }

    auto it = std::min_element(transformedSeeds.begin(),transformedSeeds.end(),[](const auto& a,const auto& b){
        return a.first < b.first;
    });
    return it->first;
}


namespace Part2
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        std::string name;
        istream >> name;
        if(name == "seeds:")
        {
            std::cout << "Working on Seeds\n";
            std::size_t seed1;
            std::size_t seed2;
            istream >> seed1;
            istream >> seed2;
            while(istream)
            {
                work.seeds.push_back({seed1,seed2});
                istream >> seed1;
                istream >> seed2;
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
            }
        }
    
        return istream;
    }
}