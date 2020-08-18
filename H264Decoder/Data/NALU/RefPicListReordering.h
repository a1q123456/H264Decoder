#pragma once
#include <IO/BitstreamReader.h>


struct RefPicListReordering
{
    bool refPicListReorderingFlagl0 = false;
    std::uint8_t reorderingOfPicNumsIdc = 0;
    std::uint8_t absDiffPicNumMinus1 = 0;
    std::uint8_t longTermPicNum = 0;

    bool refPicLIstReorderingFlagl1 = false;
    std::uint8_t reorderingOfPicNumsIdcl1 = 0;
};


