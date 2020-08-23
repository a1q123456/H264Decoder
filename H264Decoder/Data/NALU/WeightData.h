#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/LumaWeightData.h>
#include <Data/NALU/ChromaWeightData.h>

struct DecodingContext;

struct WeightData
{
    bool lumaWeightFlag = false;
    LumaWeightData lumaWeightData;

    bool chromaWeightFlag = false;
    ChromaWeightData chromaWeightData[2];

    WeightData() = default;
    explicit WeightData(DecodingContext& context, BitstreamReader& reader);


};


