#pragma once
#include <IO/BitstreamReader.h>


struct RefPicListMvcModificationData
{
    std::uint8_t modificationOfPicNumsIdc = 0;
    std::uint8_t absDiffPicNumMinus1 = 0;
    std::uint8_t longTermPicNum = 0;
    std::uint8_t absDiffViewIdxMinus1 = 0;
};


