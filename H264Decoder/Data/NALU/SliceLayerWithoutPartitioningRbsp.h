#pragma once
#include <IO/BitstreamReader.h>


struct SliceLayerWithoutPartitioningRbsp
{
    SliceHeader sliceHeader;

    SliceData sliceDSata;

    RbspSliceTrailingBits rbspSliceTrailingBits;
};


