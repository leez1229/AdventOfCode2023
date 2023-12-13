#pragma once

#include <vector>
#include <istream>
class Elf
{
public:
    void AddFoodCalories(int calories);
    int TotalCalories() const;
    friend std::istream& operator>>(std::istream& istream, Elf& elf);
private:
    std::vector<int> food;
};