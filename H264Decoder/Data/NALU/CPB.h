#pragma once
#include <IO/BitstreamReader.h>


struct CPB
{
    std::uint32_t bitRateValueMinus1 = 0;
    std::uint32_t cpbSizeValueMinus1 = 0;
    bool cbrFlag = false;
};


