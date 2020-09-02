#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\WeightData.h>


struct DecodingContext;
struct NALUnit;

struct PredWeightTable
{
    std::uint16_t lumaLog2WeightDenom = 0;
    std::uint16_t chromaLog2WeightDenom = 0;

    std::vector<WeightData> weightDataL0;
    std::vector<WeightData> weightDataL1;

    PredWeightTable() = default;
    explicit PredWeightTable(DecodingContext& context, BitstreamReader& reader);
};


