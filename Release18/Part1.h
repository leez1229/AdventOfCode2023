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

namespace Part1
{
    struct Verticies
    {
        int y;
        int x;
        std::string color;
    };
   
    class Work
    {
    public:
        Work();
        std::size_t Output();
        friend std::istream& operator>>(std::istream& istream, Part1::Work& work);
    private:
        std::vector<Verticies> plane;
        int perimiter {0};

    };
}