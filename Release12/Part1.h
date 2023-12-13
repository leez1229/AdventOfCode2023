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

namespace Part1
{
    enum class ZONE_STATE
    {
        UNKNOWN,
        POSSIBLY_FIXED,
        FIXED,
        BROKEN
    };
    struct Zone
    {
        std::size_t contiguousCount;
        ZONE_STATE state;
    };

    class Work
    {
    public:
        Work();
        std::size_t Output();
        friend std::istream& operator>>(std::istream& istream, Part1::Work& work);
    private:
        std::string input;
        std::vector<int> groups;
    
    };
}