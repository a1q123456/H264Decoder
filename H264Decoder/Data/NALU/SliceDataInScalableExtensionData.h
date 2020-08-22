#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\MacroBlockLayerInScalableExtension.h>


struct SliceDataInScalableExtensionData
{
    std::uint8_t mbSkipRun = 0;
    bool mbSkipFlag = false;
    bool mbFieldDecodingFlag = false;
    MacroBlockLayerInScalableExtension macroBlockLayerInScalableExtension;

    bool endOfSliceFlag = false;

};


