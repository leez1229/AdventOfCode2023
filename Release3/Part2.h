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
    struct SchematicPiece
    {
        std::string partNumber;
        bool isNumber {false};
    };

    class Work
    {
    public:
        Work();
        int Output();
        friend std::istream& operator>>(std::istream& istream, Work& work);
    private:
        std::vector<std::vector<SchematicPiece>> board;
    };
}