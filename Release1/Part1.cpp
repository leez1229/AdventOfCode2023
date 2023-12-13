#include "Part1.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>

Part1::Part1()
{
}

int Part1::Output()
{
    int sum{0};
    std::for_each(numbers.begin(),numbers.end(),[&sum](int n){
        sum += n;
    });
    return sum;
}

std::istream& operator>>(std::istream& istream, Part1& part1)
{
    std::string input;
    istream >> input;
    auto firstDigit = std::find_if(input.begin(),input.end(),[](const char& s){
        return std::isdigit(s);
    });
    auto lastDigit = std::find_if(input.rbegin(),input.rend(),[](const char& s){
        return std::isdigit(s);
    });
    std::string combinedDigit = std::string{(*firstDigit)} +  std::string{(*lastDigit)};
    part1.numbers.push_back(atoi(combinedDigit.c_str()));
    return istream;
}