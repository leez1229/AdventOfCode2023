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

namespace Part2
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
        Work(std::map<std::string,std::vector<std::pair<std::vector<int>,std::size_t>>>& cache);
        std::size_t Output();
        friend std::istream& operator>>(std::istream& istream, Part2::Work& work);
    private:
        std::size_t MoveSprings(const std::string& str,std::vector<int> groups);
        bool CheckCache(const std::string& str, std::vector<int> groups, std::size_t& value);
        std::size_t Cache(const std::string& str, std::vector<int> groups, std::size_t value);
        std::string input;
        std::vector<int> groups;
        std::size_t sum {0};
        std::map<std::string,std::vector<std::pair<std::vector<int>,std::size_t>>>& cache;
    };
}