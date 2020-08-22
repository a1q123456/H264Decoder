#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\MacroBlockLayerIn3DAVCExtension.h>


struct SliceDataIn3DAVCExtensionData
{
    std::uint8_t mbSkipRun = 0;
    bool mbSkipTypeFlag = false;
    bool mbVsskipFlag = false;
    bool mbSkipFlag = false;
    std::uint8_t mbSkipRunType = 0;
    bool mbAlcSkipFlag = false;
    bool mbFieldDecodingFlag = false;

    MacroBlockLayerIn3DAVCExtension macroBlockLayerIn3DAVCExtension;

    bool endOfSliceFlag = false;
};


