#include "pch.h"
#include "MvcScalableNesting.h"
#include <Data\NALU\SEI\SEIMessage.h>


MvcScalableNesting::MvcScalableNesting(BitstreamReader& reader, DecodingContext& context, NALUnit& nalu)
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
                seiViewId.emplace_back(reader.readBits<std::uint16_t, 10>());
            }
        }
    }
    else
    {
        numViewComponentsOpMinus1 = reader.readExpoGlomb();
        for (std::uint32_t i = 0; i <= numViewComponentsOpMinus1; i++)
        {
            seiOpViewId.emplace_back(reader.readBits<std::uint16_t, 10>());
        }
        seiOpTemporalId = reader.readBits<std::uint8_t, 3>();
    }
    while (!reader.byteAligned())
    {
        reader.readBits<std::uint8_t, 1>();
    }
    seiMessage = SEIMessage{ context, reader, nalu };
}
