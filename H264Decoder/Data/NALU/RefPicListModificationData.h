#pragma once
#include <IO/BitstreamReader.h>


struct RefPicListModificationData
{
    std::uint8_t modificationOfPicNumIdc = 0;
    std::uint8_t absDiffPicNUmMInus1 = 0;
    std::uint8_t longTermPicNum = 0;

    RefPicListModificationData() = default;
    explicit RefPicListModificationData(BitstreamReader& reader)
    {
        modificationOfPicNumIdc = reader.readExpoGlomb();
        if (modificationOfPicNumIdc == 0 || modificationOfPicNumIdc == 1)
        {
            absDiffPicNUmMInus1 = reader.readExpoGlomb();
        }
        else if (modificationOfPicNumIdc == 2)
        {
            longTermPicNum = reader.readExpoGlomb();
        }
    }
};



