#pragma once
#include <IO/BitstreamReader.h>


struct Intra4x4Pred
{
    bool prevIntra4x4PredModeFlag = false;
    std::uint8_t remIntra4x4PredMode = 0;
};


