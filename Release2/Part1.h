#pragma once

#include <stack>
#include <istream>
#include <map>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>
#include <set>

class Part1
{
public:
    Part1();
    int Output();
    friend std::istream& operator>>(std::istream& istream, Part1& part1);
private:
    std::vector<int> possibleGames;
};