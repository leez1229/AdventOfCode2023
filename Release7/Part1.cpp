#include "Part1.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>

namespace
{
    enum class HAND_TYPES
    {
        HIGH_CARD = 0,
        ONE_PAIR = 1,
        TWO_PAIR = 2,
        THREE_OF_A_KIND = 3,
        FULL_HOUSE = 4,
        FOUR_OF_A_KIND = 5,
        FIVE_OF_A_KIND = 6,
    };

    HAND_TYPES WhatHand(const std::string& hand)
    {
        std::map<char,int> content;
        std::for_each(hand.begin(),hand.end(),[&content](char c){
            content[c]++;
        });

        std::vector<int> cardCount;
        std::for_each(content.begin(),content.end(),[&](const std::pair<char,int>& p){
            cardCount.push_back(p.second);
        });
        std::sort(cardCount.begin(),cardCount.end(),std::greater<int>());
        int set1 = cardCount[0];
        int set2 = 0;
        if(cardCount.size() > 1)
            set2 = cardCount[1];
        if(set1 == 5 || set2 == 5)
            return HAND_TYPES::FIVE_OF_A_KIND;
        else if(set1 == 4 || set2 == 4)
            return HAND_TYPES::FOUR_OF_A_KIND;
        else if(set1 + set2 == 5)
            return HAND_TYPES::FULL_HOUSE;
        else if(set1 == 2 && set2 == 2)
            return HAND_TYPES::TWO_PAIR;
        else if(set1 + set2 == 4)
            return HAND_TYPES::THREE_OF_A_KIND;
        if(set1 + set2 == 3)
            return HAND_TYPES::ONE_PAIR;
        else
            return HAND_TYPES::HIGH_CARD;
    }
    const std::map<char,int> cardValues {
        {'A',14},
        {'K',13},
        {'Q',12},
        {'J',11},
        {'T',10},
        {'9',9},
        {'8',8},
        {'7',7},
        {'6',6},
        {'5',5},
        {'4',4},
        {'3',3},
        {'2',2}
    };
    //-1 A < B
    //0 A == B
    //1 A > B
    int IsCardBigger(char a, char b)
    {
        if(a == b)
            return 0;
        int aValue = cardValues.at(a);
        int bValue = cardValues.at(b);
        return aValue < bValue ? -1 : 1;
    }
}

Part1::Work::Work()
{
}

std::size_t Part1::Work::Output()
{
    std::vector<std::pair<HAND_TYPES,std::pair<std::string,int>>> categorizedHands;
    for(auto& hand: hands)
    {
       HAND_TYPES handType = WhatHand(hand.first);
       categorizedHands.push_back({handType,hand});
    }
    std::sort(categorizedHands.begin(),categorizedHands.end(),[](const decltype(categorizedHands)::value_type& a, const decltype(categorizedHands)::value_type& b){
        if(a.first == b.first)
        {
            for(int i = 0; i < 5; ++i)
            {
                int value = IsCardBigger(a.second.first.at(i),b.second.first.at(i));
                if(value != 0)
                {
                    return value == -1 ? true : false;
                }
            }
        }
        bool isLess = a.first < b.first;
        return isLess;
    });

    std::size_t sum {0};
    for(int i = 0; i < categorizedHands.size();++i)
    {
        sum += categorizedHands[i].second.second * (i + 1);
    }
    return sum;
}


namespace Part1
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        std::string cards;
        std::size_t bid;
        istream >> cards;
        istream >> bid;
        work.hands.push_back({cards,bid});
        return istream;
    }
}