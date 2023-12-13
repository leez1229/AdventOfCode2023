#include "FileLineReader.h"
#include "FileBlockReader.h"
#include "Part1.h"
#include "Part2.h"
#include <vector>

using namespace Part2;

int main(int argc, char** argv)
{
    FileLineReader file("../../in.txt","");
    // FileBlockReader file("../../in.txt","");
    std::vector<Work> workers;
    workers.push_back(Work{});
    while(file.ParseToObject(workers.back()))
    {
        workers.push_back(Work{});
    }
    long long int sum {0};
    for(auto& w : workers)
    {
        sum += w.Output();
    }
    std::cout << "Answer: " << sum << '\n';
    //std::cout << "Answer: " << work.Output() << '\n';
}