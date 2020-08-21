#include "pch.h"
#include "ScalableNesting.h"

ScalableNesting::ScalableNesting(DecodingContext& context, NALUnit nalu, BitstreamReader& reader)
{
    allLayerRepresentationsInAuFlag = reader.readBits<bool, 1>();
    if (!allLayerRepresentationsInAuFlag)
    {
        numLayerRepresentationsMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= numLayerRepresentationsMinus1; i++)
        {
            layerRepresentations.emplace_back(reader);
        }
        seiTemporalId = reader.readBits<std::uint8_t, 3>();
    }
    while (!reader.byteAligned())
    {
        seiNestingZeroBit = reader.readBits<std::uint8_t, 1>();
        if (seiNestingZeroBit != 0)
        {
            throw std::runtime_error("not supported");
        }
    }
    do
    {
        seiMessage.emplace_back(SEIMessage{});
    } while (reader.moreData());
}
