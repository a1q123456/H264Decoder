#pragma once
#include <IO/BitstreamReader.h>


struct SliceDataInScalableExtension
{
    std::vector<BoolType> cabacAlignmentOneBit;

    std::vector<SliceDataInScalableExtensionData> sliceDataInScalableExtensionData;
};


