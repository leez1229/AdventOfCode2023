#include "FileLineReader.h"
#include "FileBlockReader.h"
#include "Part1.h"
#include "Part2.h"
#include "Part3.h"
#include <vector>

using namespace Part2;

int main(int argc, char** argv)
{
    FileLineReader file("../../in.txt","");
    // FileBlockReader file("../../in.txt","");
    std::vector<Work> workers;
    //Work* work = &workers.back();
    std::map<std::string,std::vector<std::pair<std::vector<int>,std::size_t>>> cache;
    while(true)
    {
        workers.push_back(Work{cache});
        if(!file.ParseToObject(workers.back()))
        {
            workers.pop_back();
            break;
        }
        
    }
    
    std::size_t sum{0};
    int i = 0;
    for(auto&w: workers)
    {
        std::size_t s = w.Output();
        sum += s;
        std::cout << ++i << '\n';
    }
    std::cout << "Answer: " << sum << '\n';
}