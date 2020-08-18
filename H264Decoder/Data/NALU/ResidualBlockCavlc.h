#pragma once
#include <IO/BitstreamReader.h>


struct ResidualBlockCavlc
{
    CeV coeffToken;
    bool trailingOnesSignFlag = false;
    CeV levelPrefix;
    std::uint8_t levelSuffix = 0;
    CeV totalZeros;
    CeV runBefore;
};

