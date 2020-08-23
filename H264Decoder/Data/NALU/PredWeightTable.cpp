#include "pch.h"
#include "PredWeightTable.h"
#include <Data/DecodingContext.h>
#include <Data/NALUnit.h>
#include <Data\NALU\SliceHeaderInScalableExtension.h>
#include <Data\NALU\SliceHeaderIn3DAVCExtension.h>

PredWeightTable::PredWeightTable(DecodingContext& context, BitstreamReader& reader)
{
    lumaLog2WeightDenom = reader.readExpoGlomb();
    if (context.currentSPS().chromaArrayType != 0)
    {
        chromaLog2WeightDenom = reader.readExpoGlomb();
    }

    auto numRefIdxL0ActiveMinus1 = 0;
    auto numRefIdxL1ActiveMinus1 = 0;
    auto sliceType = 0;

    auto&& sliceHeader = context.currentSliceHeader();
    if (context.sliceHeaderIsSVC())
    {
        auto&& header = std::get<SliceHeaderInScalableExtension>(sliceHeader);
        numRefIdxL0ActiveMinus1 = header.numRefIdxL0ActiveMinus1;
        numRefIdxL1ActiveMinus1 = header.numRefIdxL1ActiveMinus1;
        sliceType = header.sliceType;
    }
    else if (context.sliceHeaderIs3DAVC())
    {
        auto&& header = std::get<SliceHeaderIn3DAVCExtension>(sliceHeader);
        numRefIdxL0ActiveMinus1 = header.numRefIdxL0ActiveMinus1;
        numRefIdxL1ActiveMinus1 = header.numRefIdxL1ActiveMinus1;
        sliceType = header.sliceType;
    }
    else if (context.hasSliceHeader())
    {
        auto&& header = std::get<SliceHeader>(sliceHeader);
        numRefIdxL0ActiveMinus1 = header.numRefIdxL0ActiveMinus1;
        numRefIdxL1ActiveMinus1 = header.numRefIdxL1ActiveMinus1;
        sliceType = header.sliceType;
    }
    else
    {
        throw std::runtime_error("no slice header");
    }
    
    for (auto i = 0; i <= numRefIdxL0ActiveMinus1; i++)
    {
        weightDataL0.emplace_back(context, reader);
    }
    if (sliceType % 5 == 1)
    {
        for (auto i = 0; i <= numRefIdxL1ActiveMinus1; i++)
        {
            weightDataL1.emplace_back(context, reader);
        }
    }
}

