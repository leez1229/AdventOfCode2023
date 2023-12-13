#include "Part1.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    bool CheckForSymbolsAboveBelow(const std::vector<char>& row,const std::vector<std::size_t>& indicies)
    {
        bool isPartNumber = std::any_of(indicies.begin(),indicies.end(),[&](std::size_t i){
            return row[i] != '.' && !isdigit(row[i]);
        });

        if(!isPartNumber && !indicies.empty())
        {
            
            std::size_t f = indicies.front();
            std::size_t b = indicies.back();
            if(f > 0)
            {
                std::size_t beforeNumber = f - 1;
                if (row[beforeNumber] != '.' && !isdigit(row[beforeNumber]))
                {
                    isPartNumber = true;
                }
            }
            if(b < row.size() - 1)
            {
                std::size_t afterNumber = b + 1;
                if (row[afterNumber] != '.' && !isdigit(row[afterNumber]))
                {
                    isPartNumber = true;
                }
            }
        }
        return isPartNumber;
    }

    bool CheckForSymbols(const std::vector<char>& row,const std::vector<std::size_t>& indicies)
    {
        bool isPartNumber {false};
        if(!indicies.empty())
        {
            std::size_t f = indicies.front();
            std::size_t b = indicies.back();
            if(f > 0)
            {
                if (row[f-1] != '.')
                {
                    isPartNumber = true;
                }
            }
            if(b < row.size() - 1)
            {
                if (row[b+1] != '.')
                {
                    isPartNumber = true;
                }
            }
        }
        return isPartNumber;
    }
}

Part1::Work::Work()
{
}

int Part1::Work::Output()
{
    std::size_t sum {0};
    for(std::size_t y = 0; y < board.size(); ++y)
    {
        std::string partNumber;
        std::vector<std::size_t> indiciesToCheck;
        for(std::size_t x = 0; x < board[y].size(); ++x)
        {
            char c = board[y][x];
            if(isdigit(c))
            {
                indiciesToCheck.push_back(x);
                partNumber.push_back(c);
            }
            else
            {
                if(!partNumber.empty())
                {
                    bool isValidPartNumber = CheckForSymbols(board[y],indiciesToCheck);
                    if(y > 0)
                        isValidPartNumber |= CheckForSymbolsAboveBelow(board[y-1],indiciesToCheck);
                    if(y < board.size() - 1)
                        isValidPartNumber |= CheckForSymbolsAboveBelow(board[y+1],indiciesToCheck);
                    if(isValidPartNumber)
                        sum += std::atoi(partNumber.c_str());
                    partNumber.clear();
                    indiciesToCheck.clear();
                }
            }
        }
        if(!partNumber.empty())
        {
            bool isValidPartNumber = CheckForSymbols(board[y],indiciesToCheck);
            if(y > 0)
                isValidPartNumber |= CheckForSymbolsAboveBelow(board[y-1],indiciesToCheck);
            if(y < board.size() - 1)
                isValidPartNumber |= CheckForSymbolsAboveBelow(board[y+1],indiciesToCheck);
            if(isValidPartNumber)
                sum += std::atoi(partNumber.c_str());
            partNumber.clear();
            indiciesToCheck.clear();
        }
    }
    return sum;
}


namespace Part1
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        char c;
        std::vector<char> row;
        istream >> c;
        while(istream)
        {
            row.push_back(c);
            istream >> c;
        }
        work.board.push_back(row);
        return istream;
    }
}