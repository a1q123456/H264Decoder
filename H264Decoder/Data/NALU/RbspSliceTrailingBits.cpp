#include "pch.h"
#include <Data/NALU/RbspSliceTrailingBits.h>
#include <Data/DecodingContext.h>

RbspSliceTrailingBits::RbspSliceTrailingBits(DecodingContext& context, BitstreamReader& reader)
{
    rbspTrailingBits = RbspTrailingBits{ reader };
    if (context.currentPPS().entropyCodingModeFlag)
    {
        while (reader.moreData())
        {
            cabacZeroWord = reader.readBits<std::uint16_t>(16);
        }
    }
}
