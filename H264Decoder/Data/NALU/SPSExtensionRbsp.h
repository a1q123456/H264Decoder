#pragma once
#include <IO/BitstreamReader.h>


struct SPSExtensionRbsp
{
    std::uint8_t spsId = 0;
    std::uint8_t auxFormatIdx = 0;

    bool bitDepthAuxMinus8 = false;
    bool alphaIncrFlag = false;
    std::uint8_t alphaOpaqueValue = 0;
    std::uint8_t alphaTransparentValue = 0;

    bool additionalExtensionFlag = false;

    RbspTrailingBits rbspTrailingBits;
};


