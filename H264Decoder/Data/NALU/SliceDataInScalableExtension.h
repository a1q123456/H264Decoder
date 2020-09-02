#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\SliceDataInScalableExtensionData.h>


struct DecodingContext;

struct SliceDataInScalableExtension
{
    std::vector<std::uint8_t> cabacAlignmentOneBit;

    std::vector<SliceDataInScalableExtensionData> sliceDataInScalableExtensionData;

    SliceDataInScalableExtension() = default;
    explicit SliceDataInScalableExtension(DecodingContext& context, BitstreamReader& reader);
};


