#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\SliceHeaderIn3DAVCExtension.h>
#include <Data\NALU\SliceDataInScalableExtension.h>
#include <Data\NALU\SliceHeaderInScalableExtension.h>
#include <Data\NALU\SliceData.h>
#include <Data\NALU\RbspSliceTrailingBits.h>
#include <Data\NALU\SliceDataIn3DAVCExtension.h>


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


