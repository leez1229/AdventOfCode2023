#pragma once

#include <stack>
#include <istream>
#include <map>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>
#include <set>

namespace Part1
{
    class Work
    {
    public:
        Work();
        int Output();
        friend std::istream& operator>>(std::istream& istream, Part1::Work& work);
    private:
        int winningCardTotals {0};
    };
}