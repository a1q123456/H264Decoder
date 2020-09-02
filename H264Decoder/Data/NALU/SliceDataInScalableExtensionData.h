#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\MacroBlockLayerInScalableExtension.h>

struct DecodingContext;

struct SliceDataInScalableExtensionData
{
    std::uint16_t mbSkipRun = 0;
    bool mbSkipFlag = false;
    bool mbFieldDecodingFlag = false;
    MacroBlockLayerInScalableExtension macroBlockLayerInScalableExtension;

    bool endOfSliceFlag = false;

    SliceDataInScalableExtensionData() = default;
};


