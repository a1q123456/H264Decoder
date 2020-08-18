#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\WeightData.h>


struct PredWeightTable
{
    std::uint8_t lumaLog2WeightDenom = 0;
    std::uint8_t chromaLog2WeightDenom = 0;
    std::vector<WeightData> weightDatal0;

    std::vector<WeightData> weightDatal1;
};


