#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/LumaWeightData.h>
#include <Data/NALU/ChromaWeightData.h>

struct WeightData
{
    bool lumaWeightFlag = false;
    LumaWeightData lumaWeightData;
    bool chromaWeightFlag = false;
    std::array<ChromaWeightData, 2> chromaWeightData;

};


