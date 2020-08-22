#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\SliceDataInScalableExtensionData.h>


struct SliceDataInScalableExtension
{
    std::vector<BoolType> cabacAlignmentOneBit;

    std::vector<SliceDataInScalableExtensionData> sliceDataInScalableExtensionData;
};


