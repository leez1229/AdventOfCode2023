#include "FileLineReader.h"
#include "FileBlockReader.h"
#include "Part1.h"
#include "Part2.h"
#include "Part3.h"
#include <vector>

using namespace Part2;

int main(int argc, char** argv)
{
    // FileLineReader file("../../test.txt","");
    FileBlockReader file("../../in.txt","");
    std::vector<Work> workers;
    //Work* work = &workers.back();
    while(true)
    {
        workers.push_back(Work{});
        if(!file.ParseToObject(workers.back()))
        {
            workers.pop_back();
            break;
        }
        
    }
    
    std::size_t sum{0};
    for(auto&w: workers)
    {
        std::size_t s = w.Output();
        sum += s;
    }
    std::cout << "Answer: " << sum << '\n';
}