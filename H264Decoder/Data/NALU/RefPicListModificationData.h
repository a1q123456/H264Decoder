#pragma once
#include <IO/BitstreamReader.h>


struct RefPicListModificationData
{
    std::uint8_t modificationOfPicNumIdc = 0;
    std::uint8_t absDiffPicNUmMInus1 = 0;
    std::uint8_t longTermPicNum = 0;
};



