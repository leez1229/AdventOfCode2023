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
    struct Sequence
    {
        Sequence(Sequence* parent)
        :prev(parent)
        {}
        std::unique_ptr<Sequence> next;
        Sequence* prev;
        std::vector<long long int> oaisis;
    };

    class Work
    {
    public:
        Work();
        long long int Output();
        friend std::istream& operator>>(std::istream& istream, Part1::Work& work);
    private:
       Sequence root{nullptr};
    };
}