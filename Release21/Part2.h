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
    

    class Work
    {
    public:
        Work();
        std::size_t Output();
        friend std::istream& operator>>(std::istream& istream, Part2::Work& work);
    private:
        std::vector<std::vector<char>> map;
        std::pair<std::size_t,std::size_t> startPos;
    };
}