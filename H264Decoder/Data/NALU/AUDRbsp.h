#pragma once
#include <IO/BitstreamReader.h>


struct AUDRbsp
{
    std::uint8_t primaryPicType = 0;
    RbspTrailingBits rbspTrailingBits;
};


