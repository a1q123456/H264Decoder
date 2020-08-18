#pragma once
#include <IO/BitstreamReader.h>


struct FilterDataRbsp
{
    std::vector<std::uint8_t> ffBytes;

    RbspTrailingBits rbspTrailingBits;
};


