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
    class Work
    {
    public:
        Work();
        std::size_t Output();
        friend std::istream& operator>>(std::istream& istream, Part2::Work& work);
    private:
        std::vector<std::vector<char>> row;
        std::vector<std::vector<char>> col;
    };
}