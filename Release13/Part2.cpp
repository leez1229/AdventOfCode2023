#include "Part2.h"
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

    

    int IsFrontMirror(std::vector<std::vector<char>>& col)
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
        return -1;
    }
    int IsBackMirror(std::vector<std::vector<char>>& col)
    {
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

    int CheckBoth(std::vector<std::vector<char>>& col)
    {
        int count = IsFrontMirror(col);
        if(count == -1)
            count = IsBackMirror(col);
        return count;
    }
}

Part2::Work::Work()
{
}

std::size_t Part2::Work::Output()
{
    int ogH = CheckBoth(row);
    int ogV = CheckBoth(col);
    int x {0};
    int y {0};
    while(true)
    {
        char& rC = row[y][x];
        char& cC = col[x][y];
        char oC = rC;
        rC = '#';
        cC = '#';
        if(rC != cC)
        {
            throw std::logic_error("Chars are not the same");
        }

        if(oC == '#')
        {
            rC = '.';
            cC = '.';
        }
        
        int h = IsFrontMirror(row);
        if(h != -1 && h != ogH)
            return h * 100;
        else
        {
            h = IsBackMirror(row);
            if(h != -1 && h != ogH)
                return h * 100;
        }

        int v = IsFrontMirror(col);
        if(v != -1 && v != ogV)
            return v;
        else
        {
            v = IsBackMirror(col);
            if(v != -1 && v != ogV)
                return v;
        }
        rC = oC;
        cC = oC;

        if(x++ == row[y].size() - 1)
        {
            x = 0;
            y++;
        }
    }

    // int h = IsHorizontal(row);
    // if(h != -1)
    //     return h * 100;
    // int v = IsHorizontal(col);
    // return v;
}

namespace Part2
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