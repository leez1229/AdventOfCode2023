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
    struct Mapper
    {
        Mapper* linkedMap{nullptr};
        std::vector<std::array<std::size_t,3>> lines;
    };

    class Work
    {
    public:
        Work();
        std::size_t Output();
        friend std::istream& operator>>(std::istream& istream, Part1::Work& work);
    private:
        std::vector<std::vector<char>> graph;
        std::vector<std::pair<std::size_t,std::size_t>> galaxies;
    };
}