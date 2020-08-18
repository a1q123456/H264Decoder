#include "pch.h"
#include "DepthRange.h"
#include <Data/DecodingContext.h>

DepthRange::DepthRange(DecodingContext& context, BitstreamReader& reader, int numViews, int predDirection, int index)
{
    zNearFlag = reader.readBits<std::uint8_t, 1>();
    zFarFlag = reader.readBits<std::uint8_t, 1>();

    if (zNearFlag)
    {
        threeDVAcquisitionElement.FromBitstream(context, reader, index, numViews, 0, predDirection, 7,
            0, context.currentDPS().zNearSign, context.currentDPS().zNearExp, context.currentDPS().zNearMantissa, context.currentDPS().zNearManLen);
    }
    if (zFarFlag)
    {
        threeDVAcquisitionElement.FromBitstream(context, reader, index, numViews, 0, predDirection, 7,
            0, context.currentDPS().zFarSign, context.currentDPS().zFarExp, context.currentDPS().zFarMantissa, context.currentDPS().zFarManLen);
    }
}
