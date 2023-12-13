#include "FileLineReader.h"
#include "FileBlockReader.h"
#include "Part1.h"
#include "Part2.h"
#include <vector>

int main(int argc, char** argv)
{
    FileLineReader file("../../in.txt","");
    //FileBlockReader file("in.txt","");
    Part2 part;
    while(file.ParseToObject(part));
    
    std::cout << "Answer: " << part.Output() << '\n';
}