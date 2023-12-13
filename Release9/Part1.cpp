#include "Part1.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>


namespace
{
    Part1::Sequence& GenerateSequence(Part1::Sequence& root)
    {
        if(std::all_of(root.oaisis.begin(),root.oaisis.end(),[](long long int num){return num == 0;}))
        {
            return root;
        }

        Part1::Sequence* currentSequence = &root;

        auto tempSeq = std::make_unique<Part1::Sequence>(currentSequence);
        auto& currentOaisisValues = root.oaisis;
        for(long long int i = 0; i < currentOaisisValues.size() - 1;++i)
        {
            tempSeq->oaisis.push_back(currentOaisisValues[i+1] - currentOaisisValues[i]);
        }
        currentSequence->next = std::move(tempSeq);
        currentSequence = currentSequence->next.get();
        return GenerateSequence(*currentSequence);
    }

    long long int CalculateNextSequenceNumber(Part1::Sequence& seq)
    {
        if(seq.next)
        {
            auto& oaisis = seq.oaisis;
            oaisis.push_back(oaisis.back() + seq.next->oaisis.back());
        }
        else
        {
            seq.oaisis.push_back(0);
        }

        if(seq.prev)
            return CalculateNextSequenceNumber(*seq.prev);
        else
            return seq.oaisis.back();
    }
}

Part1::Work::Work()
{
}

long long int Part1::Work::Output()
{
    
    auto& fullSequence = GenerateSequence(root);

    long long int num = CalculateNextSequenceNumber(fullSequence);
    return num;
}


namespace Part1
{
    std::istream& operator>>(std::istream& istream, Work& work)
    {
        long long int num;
        istream >> num;
        while(istream)
        {
            work.root.oaisis.push_back(num);
            istream >> num;
        }
        return istream;
    }
}