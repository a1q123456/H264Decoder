#pragma once
#include <IO/BitstreamReader.h>


struct SliceDataPartitionALayerRbsp
{
    SliceHeader sliceHeader;
    std::uint8_t sliceID = 0;
    SliceData sliceData;

    RbspSliceTrailingBits rbspSliceTrailingBits;
};


