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
#include <queue>

namespace Part2
{
    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        Right,
        NONE,
    };

    struct Path
    {
        int heatLoss;
        Direction previousDirection {Direction::NONE};
        std::pair<int,int> currentTile;
        // std::vector<std::pair<int,int>> debugPath;
        int inARowCount {0};
        Direction inARowDirection {Direction::NONE};
    };
    struct Comp
    {
        bool operator()(const Path& l, const Path& r) const { return l.heatLoss > r.heatLoss; }
    };
    class Work
    {
    public:
        Work();
        std::size_t Output();
        friend std::istream& operator>>(std::istream& istream, Part2::Work& work);
    private:
        std::vector<std::vector<int>> input;
        std::vector<std::vector<std::vector<std::array<int,11>>>> distances;
        std::vector<std::vector<std::array<bool,4>>> visited;
        std::priority_queue<Path,std::vector<Path>,Comp> pQueue;
        std::vector<Path> GetPossiblePaths(const Path& path);
        void RunPaths();

    };
}