#pragma once
#include <IO/BitstreamReader.h>


struct RbspSliceTrailingBits
{
    RbspTrailingBits rbspTrailingBits;
    std::uint8_t cabacZeroWord = 0;

    RbspSliceTrailingBits() = default;
    explicit RbspSliceTrailingBits(DecodingContext& context, BitstreamReader& reader)
    {
        if (context.currentPPS().entropyCodingModeFlag)
        {
            while (reader.moreData())
            {
                cabacZeroWord = reader.readBits<std::uint16_t>(16);
            }
        }
    }

};


