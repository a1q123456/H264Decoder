#pragma once
#include <IO/BitstreamReader.h>


struct MvcScalableNesting
{
    bool operationPointFlag = false;
    bool allViewComponentsInAuFlag = false;
    std::uint32_t numViewComponentsMinus1;

    std::vector<std::uint16_t> seiViewId;

    std::uint32_t numViewComponentsOpMinus1 = 0;
    std::vector<std::uint16_t> seiOpViewId;
    std::uint8_t seiOpTemporalId = 0;

    std::uint8_t seiNestingZeroBit = 0;
    SEIMessage seiMessage;

    MvcScalableNesting() = default;
    explicit MvcScalableNesting(BitstreamReader& reader)
    {
        operationPointFlag = reader.readBits<bool, 1>();
        if (!operationPointFlag)
        {
            allViewComponentsInAuFlag = reader.readBits<bool, 1>();
            if (!allViewComponentsInAuFlag)
            {
                numViewComponentsMinus1 = reader.readExpoGlomb();
                for (auto i = 0; i <= numViewComponentsMinus1; i++)
                {
                    seiViewId.emplace_back(reader.readBits<std::uint16_t, 10>());
                }
            }
        }
        else
        {
            numViewComponentsOpMinus1 = reader.readExpoGlomb();
            for (auto i = 0; i <= numViewComponentsOpMinus1; i++)
            {
                seiOpViewId.emplace_back(reader.readBits<std::uint16_t, 10>());
            }
            seiOpTemporalId = reader.readBits<std::uint8_t, 3>();
        }
        while (!reader.byteAligned())
        {
            reader.readBits<std::uint8_t, 1>();
        }
        // TODO sei message
    }
};



