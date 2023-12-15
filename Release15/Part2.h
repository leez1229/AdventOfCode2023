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
#include <list>

namespace Part2
{
    struct Lense
    {
        std::string label;
        char operation;
        int val {0};
    };

    class Work
    {
    public:
        Work();
        std::size_t Output();
        friend std::istream& operator>>(std::istream& istream, Part2::Work& work);
    private:
        std::vector<Lense> input;
        std::array<std::list<Lense>,256> boxes;

        void PerformOperation(const Part2::Lense& l);
    };
}