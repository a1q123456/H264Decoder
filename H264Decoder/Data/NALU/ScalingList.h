#pragma once
#include <IO/BitstreamReader.h>


inline void readScalingList(BitstreamReader& rbspReader, std::vector<int>& scalingList, std::size_t sizeOfScalingList, bool& useDefaultScalingMatrixFlag)
{
    auto lastScale = 8;
    auto nextScale = 8;

    for (std::size_t j = 0; j < sizeOfScalingList; j++)
    {
        if (nextScale != 0)
        {
            auto currentDeltaScale = rbspReader.readSignedExpoGlomb();
            nextScale = (lastScale + currentDeltaScale + 256) % 256;
            useDefaultScalingMatrixFlag = j == 0 && nextScale == 0;
        }
        scalingList[j] = (nextScale == 0) ? lastScale : nextScale;
        lastScale = scalingList[j];
    }

}

struct ScalingList
{
    bool useDefaultFlag = false;
    std::vector<int> scalingList;
};


