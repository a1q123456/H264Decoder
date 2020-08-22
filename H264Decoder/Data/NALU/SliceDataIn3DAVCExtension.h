#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/SliceDataIn3DAVCExtensionData.h>


struct SliceDataIn3DAVCExtension
{
    std::uint8_t cabacAlignmentOneBit = 0;

    std::vector<SliceDataIn3DAVCExtensionData> sliceDataIn3DAVCExtensionData;
};


