#pragma once
#include <IO/BitstreamReader.h>


struct SliceDataPartitionCLayerRbsp
{
    std::uint8_t sliceID = 0;
    std::uint8_t redundantPicCnt = 0;
    SliceData sliceData;

    RbspSliceTrailingBits rbspSliceTrailingBits;
};


