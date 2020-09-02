#include "pch.h"
#include <Data/DecodingContext.h>
#include "SliceDataInScalableExtension.h"

SliceDataInScalableExtension::SliceDataInScalableExtension(DecodingContext& context, BitstreamReader& reader)
{
    if (context.currentPPS().entropyCodingModeFlag)
    {
        while (!reader.byteAligned())
        {
            cabacAlignmentOneBit = reader.readBits<std::uint8_t, 1>();
        }
    }
    auto currMbAddr = firstMbInSlice * (1 + mbaffFrameFlag);
    auto moreDataFlag = true;
    auto prevMbSkipped = false;

    do
    {
        sliceDataInScalableExtensionData.emplace_back(reader);
    }
}
