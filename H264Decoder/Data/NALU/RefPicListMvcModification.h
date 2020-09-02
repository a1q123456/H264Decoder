#pragma once
#include <IO/BitstreamReader.h>


struct RefPicListMvcModification
{
    struct RefPicListMvcModificationData
    {
        std::uint8_t modificationOfPicNumsIdc = 0;
        std::uint8_t absDiffPicNumMinus1 = 0;
        std::uint8_t longTermPicNum = 0;
        std::uint8_t absDiffViewIdxMinus1 = 0;
    };

    bool refPicListModificationFlagl0 = false;
    std::vector<RefPicListMvcModificationData> datal0;

    bool refPicListModificationFlagl1 = false;
    std::vector<RefPicListMvcModificationData> datal1;
};


