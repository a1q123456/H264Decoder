#pragma once
#include <IO/BitstreamReader.h>


struct CPB
{
    std::uint16_t bitRateValueMinus1 = 0;
    std::uint16_t cpbSizeValueMinus1 = 0;
    bool cbrFlag = false;
};


