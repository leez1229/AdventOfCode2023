#pragma once

#include <stack>
#include <istream>
#include <map>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>
#include <set>

class Part2
{
public:
    Part2();
    int Output();
    friend std::istream& operator>>(std::istream& istream, Part2& part1);
private:
    std::vector<int> numbers;
};