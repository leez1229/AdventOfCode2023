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
    Work work{};
    while(file.ParseToObject(work));
        
    std::cout << "Answer: " << work.Output() << '\n';
}