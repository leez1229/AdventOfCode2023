#include "Elf.h"
#include <algorithm>

void Elf::AddFoodCalories(int calories)
{
    food.push_back(calories);
}

int Elf::TotalCalories() const
{
    int calSum = 0;
    std::for_each(food.begin(),food.end(),[&calSum](int cal){
        calSum += cal;
    });
    return calSum;
}

std::istream& operator>>(std::istream& istream, Elf& elf)
{
    std::string input;
    istream >> input;
    elf.AddFoodCalories(std::atoi(input.c_str()));
    return istream;
}