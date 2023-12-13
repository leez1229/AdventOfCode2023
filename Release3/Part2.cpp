#include "Part2.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    std::set<std::string> CheckForTwoNumbers(const std::vector<Part2::SchematicPiece>& row, std::size_t xpos)
    {
        std::set<std::string> partNumbers;
        if(xpos > 0)
        {
            if(row[xpos - 1].isNumber)
            {
                partNumbers.emplace(row[xpos - 1].partNumber);
            }
        }
        if(xpos < row.size() - 1)
        {
            if(row[xpos + 1].isNumber)
            {
                partNumbers.emplace(row[xpos + 1].partNumber);
            }
        }
        if(row[xpos].isNumber)
        {
            partNumbers.emplace(row[xpos].partNumber);
        }
        return partNumbers;
    }
}

Part2::Work::Work()
{
}

int Part2::Work::Output()
{
    std::size_t sum {0};
    for(std::size_t y = 0; y < board.size(); ++y)
    {
        for(std::size_t x = 0; x < board[y].size(); ++x)
        {
            if(board[y][x].partNumber == "*")
            {
                std::set<std::string> sameRow = CheckForTwoNumbers(board[y],x);
                std::set<std::string> aboveRow;
                std::set<std::string> belowRow;
                if(y > 0)
                    aboveRow = CheckForTwoNumbers(board[y-1],x);
                if(y < board.size() - 1)
                    belowRow = CheckForTwoNumbers(board[y+1],x);
                std::vector<std::string> allPartNumbres;
                std::copy(sameRow.begin(),sameRow.end(),std::back_inserter(allPartNumbres));
                std::copy(aboveRow.begin(),aboveRow.end(),std::back_inserter(allPartNumbres));
                std::copy(belowRow.begin(),belowRow.end(),std::back_inserter(allPartNumbres));
                if(allPartNumbres.size() == 2)
                {
                    std::size_t ratio {1};
                    std::for_each(allPartNumbres.begin(),allPartNumbres.end(),[&ratio](std::string pnum){
                        ratio *= std::atoi(pnum.c_str());
                    });
                    sum += ratio;
                }
            }
        }
    }
    return sum;
}


namespace Part2
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        char c;
        std::vector<SchematicPiece> row;
        bool isNumber {false};
        istream >> c;
        while(istream)
        {
            std::string partNumber;
            if(isdigit(c))
            {
                isNumber = true;
                while(istream && isdigit(c))
                {
                    partNumber.push_back(c);
                    istream >> c;
                }
            }
            else
            {
                isNumber = false;
                partNumber.push_back(c);
                istream >> c;
            }
            for(std::size_t i = 0; i < partNumber.size(); ++i)
            {
                row.push_back({partNumber,isNumber});
            }
        }
        work.board.push_back(row);
        return istream;
    }
}