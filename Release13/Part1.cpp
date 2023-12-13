#include "Part1.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    int LineEqual(std::vector<std::vector<char>>& col)
    {
        for(int i = 0; i < col.size()-1;i++)
        {
            if(std::equal(col[i].begin(),col[i].end(),col[i+1].begin()))
            {
                return i+1;
            }
        }
        return 0;
    }

    bool Collapse(std::vector<std::vector<char>>& col, int lowBound,int highBound)
    {
        if(lowBound == highBound)
            return false;
        if(lowBound > highBound)
        {
            return true;
        }

        if(!std::equal(col[lowBound].begin(),col[lowBound].end(),col[highBound].begin()))
        {
            return false;
        }
        return Collapse(col,lowBound+1,highBound-1);
    }

    int IsHorizontal(std::vector<std::vector<char>>& col)
    {
        for(int i = 1; i < col.size();i++)
        {
            if(std::equal(col[0].begin(),col[0].end(),col[i].begin()))
            {
                if(Collapse(col,0,i))
                {
                    if(i % 2 == 0)
                    {
                        return i / 2;
                    }
                    return (i + 1) /2;
                }
            }
        }
        for(int i = col.size() - 2; i >= 0;i--)
        {
            int lastElement = col.size()-1;
            if(std::equal(col[lastElement].begin(),col[lastElement].end(),col[i].begin()))
            {
                if(Collapse(col,i,lastElement))
                {
                    return col.size() - (lastElement - i + 1) / 2;
                }
            }
        }
        return -1;
    }
}

Part1::Work::Work()
{
}

std::size_t Part1::Work::Output()
{
    int h = IsHorizontal(row);
    if(h != -1)
        return h * 100;
    int v = IsHorizontal(col);
    return v;
}

namespace Part1
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        int i = 0;
        char c;
        istream >> c;
        std::vector<char> row;
        
        while(istream)
        {
            if(work.col.size() <= i)
            {
                work.col.push_back(std::vector<char>{});
            }
            work.col[i++].push_back(c);
            row.push_back(c);
            istream >> c;
        }
        work.row.push_back(row);

        return istream;
    }
}