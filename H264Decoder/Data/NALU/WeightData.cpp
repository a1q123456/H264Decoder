#include "pch.h"
#include "WeightData.h"

WeightData::WeightData(DecodingContext& context, BitstreamReader& reader)
{
    lumaWeightFlag = reader.readBits<bool, 1>();
    if (lumaWeightFlag)
    {
        lumaWeightData.lumaWeight = reader.readSignedExpoGlomb();
        lumaWeightData.lumaOffset = reader.readSignedExpoGlomb();
    }
    if (context.currentSPS().chromaArrayType != 0)
    {
        chromaWeightFlag = reader.readBits<bool, 1>();
        if (chromaWeightFlag)
        {
            for (auto j = 0; j < 2; j++)
            {
                chromaWeightData[j].chromaWeight = reader.readSignedExpoGlomb();
                chromaWeightData[j].chromaOffset = reader.readSignedExpoGlomb();
            }
        }
    }
}

