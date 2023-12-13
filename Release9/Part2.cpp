#include "Part2.h"
#include <algorithm>
#include "HelperFunctions.h"
#include <array>
#include <iostream>


namespace
{
    Part2::Sequence& GenerateSequence(Part2::Sequence& root)
    {
        if(std::all_of(root.oaisis.begin(),root.oaisis.end(),[](long long int num){return num == 0;}))
        {
            return root;
        }

        Part2::Sequence* currentSequence = &root;

        auto tempSeq = std::make_unique<Part2::Sequence>(currentSequence);
        auto& currentOaisisValues = root.oaisis;
        for(long long int i = 0; i < currentOaisisValues.size() - 1;++i)
        {
            
            tempSeq->oaisis.push_back(*std::next(currentOaisisValues.begin(),i+1) - *std::next(currentOaisisValues.begin(),i));
        }
        currentSequence->next = std::move(tempSeq);
        currentSequence = currentSequence->next.get();
        return GenerateSequence(*currentSequence);
    }

    long long int CalculateNextSequenceNumber(Part2::Sequence& seq)
    {
        if(seq.next)
        {
            auto& oaisis = seq.oaisis;
            oaisis.push_front(oaisis.front() - seq.next->oaisis.front());
        }
        else
        {
            seq.oaisis.push_front(0);
        }

        if(seq.prev)
            return CalculateNextSequenceNumber(*seq.prev);
        else
            return seq.oaisis.front();
    }
}

Part2::Work::Work()
{
}

long long int Part2::Work::Output()
{
    
    auto& fullSequence = GenerateSequence(root);

    long long int num = CalculateNextSequenceNumber(fullSequence);
    return num;
}


namespace Part2
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