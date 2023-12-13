#pragma once

#include <stack>
#include <istream>
#include <map>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>
#include <set>
#include <queue>

//Improve off of Part2
namespace Part3
{
    class Work
    {
    public:
        Work();
        std::size_t Output();
        friend std::istream& operator>>(std::istream& istream, Part3::Work& work);
    private:
        std::vector<std::pair<std::set<int>,std::vector<int>>> invetory;
        std::map<std::size_t,std::size_t> heuristicCopies;
        std::map<std::size_t> copiesCreated;
        std::size_t processedCards {0};
        void ProcessQueue();
    };
}