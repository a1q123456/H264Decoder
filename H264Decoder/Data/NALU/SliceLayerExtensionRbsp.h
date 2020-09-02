#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\SliceHeaderIn3DAVCExtension.h>
#include <Data\NALU\SliceDataInScalableExtension.h>
#include <Data\NALU\SliceHeaderInScalableExtension.h>
#include <Data\NALU\SliceData.h>
#include <Data\NALU\RbspSliceTrailingBits.h>
#include <Data\NALU\SliceDataIn3DAVCExtension.h>
#include <Data\NALU\SliceHeader.h>

struct DecodingContext;
struct NALUnit;

struct SliceLayerExtensionRbsp
{
    SliceHeaderInScalableExtension sliceHeaderInScalableExtension;
    SliceDataInScalableExtension sliceDataInScalableExtension;
    SliceHeaderIn3DAVCExtension sliceHeaderIn3DAVCExtension;
    SliceDataIn3DAVCExtension sliceDataIn3DAVCExtension;
    SliceHeader sliceHeader;
    SliceData sliceData;

    RbspSliceTrailingBits rbspSliceTrailingBits;

    SliceLayerExtensionRbsp() = default;
    explicit SliceLayerExtensionRbsp(DecodingContext& context, BitstreamReader& reader, NALUnit& nal);
};


