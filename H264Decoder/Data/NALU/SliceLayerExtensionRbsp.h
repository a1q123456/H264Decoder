#pragma once
#include <IO/BitstreamReader.h>


struct SliceLayerExtensionRbsp
{
    SliceHeaderInScalableExtension sliceHeaderInScalableExtension;
    SliceDataInScalableExtension sliceDataInScalableExtension;
    SliceHeaderIn3DAVCExtension sliceHeaderIn3DAVCExtension;
    SliceDataIn3DAVCExtension sliceDataIn3DAVCExtension;
    SliceHeader sliceHeader;
    SliceData sliceData;

    RbspSliceTrailingBits rbspSliceTrailingBits;
};


