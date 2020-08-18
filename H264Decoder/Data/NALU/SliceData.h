#pragma once
#include <IO/BitstreamReader.h>


struct SliceData
{
    std::uint8_t cabacAlignmentOneBit = 0;

    std::uint8_t mbSkipRun = 0;
    std::uint8_t mbSkipFlag = 0;
    std::uint8_t mbFieldDecodingFlag = 0;
    MacroBlockLayer macroBlockLayer;

    std::uint8_t endOfSliceFlag = 0;

};


