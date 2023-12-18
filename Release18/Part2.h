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

namespace Part2
{
    struct Verticies
    {
        std::size_t y;
        std::size_t x;
        std::string color;
    };
   
    class Work
    {
    public:
        Work();
        std::size_t Output();
        friend std::istream& operator>>(std::istream& istream, Part2::Work& work);
    private:
        std::vector<Verticies> plane;
        std::size_t perimiter {0};

    };
}