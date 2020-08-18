#pragma once
#include <IO/BitstreamReader.h>


struct CPB
{
    std::uint8_t bitRateValueMinus1 = 0;
    std::uint8_t cpbSizeValueMinus1 = 0;
    bool cbrFlag = false;
};


