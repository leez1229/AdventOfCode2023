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

namespace Part2
{
    class Work
    {
    public:
        Work();
        std::size_t Output();
        friend std::istream& operator>>(std::istream& istream, Part2::Work& work);
    private:
        std::vector<std::pair<std::set<int>,std::vector<int>>> invetory;
        std::queue<std::size_t> winingScratcherQueue;
        std::size_t processedCards {0};
        void ProcessQueue();
        void WinningCard(std::size_t winningCardIndex, std::size_t matchingNumbers);
    };
}