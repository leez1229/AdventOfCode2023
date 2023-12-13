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

class Part2
{
public:
    Part2();
    int Output();
    friend std::istream& operator>>(std::istream& istream, Part2& part);
private:
    std::vector<std::array<int,3>> possibleGames;
};