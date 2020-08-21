#include "pch.h"
#include "MvcdScalableNesting.h"
#include <Data/DecodingContext.h>

MvcdScalableNesting::MvcdScalableNesting(DecodingContext& context, BitstreamReader& reader, NALUnit& nalu)
{
    operationPointFlag = reader.readBits<bool, 1>();
    if (!operationPointFlag)
    {
        allViewComponentsInAuFlag = reader.readBits<bool, 1>();
        if (!allViewComponentsInAuFlag)
        {
            numViewComponentsMinus1 = reader.readExpoGlomb();
            for (std::uint32_t i = 0; i <= numViewComponentsMinus1; i++)
            {
                viewComponents.emplace_back(reader);
            }
        }
    }
    else
    {
        seiOpTextureOnlyFlag = reader.readBits<bool, 1>();
        numViewComponentsMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= numViewComponentsOpMinus1; i++)
        {
            viewComponentOps.emplace_back(reader, seiOpTextureOnlyFlag);
        }
        seiOpTemporalId = reader.readBits<std::uint8_t, 3>();
    }

    while (!reader.byteAligned())
    {
        seiNestingZeroBit = reader.readBits<std::uint8_t, 1>();
    }

    seiMessage = SEIMessage{context, reader, nalu };
}
