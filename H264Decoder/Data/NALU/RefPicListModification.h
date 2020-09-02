#pragma once
#include <IO/BitstreamReader.h>

struct DecodingContext;

struct RefPicListModification
{
    struct RefPicListModificationData
    {
        std::uint16_t modificationOfPicNumIdc = 0;
        std::uint16_t absDiffPicNUmMinus1 = 0;
        std::uint16_t longTermPicNum = 0;

        RefPicListModificationData() = default;
        explicit RefPicListModificationData(BitstreamReader& reader)
        {
            modificationOfPicNumIdc = reader.readExpoGlomb();
            if (modificationOfPicNumIdc == 0 || modificationOfPicNumIdc == 1)
            {
                absDiffPicNUmMinus1 = reader.readExpoGlomb();
            }
            else if (modificationOfPicNumIdc == 2)
            {
                longTermPicNum = reader.readExpoGlomb();
            }
        }
    };

    bool refPicListModificationFlagl0 = false;
    std::vector<RefPicListModificationData> refPicListModificationDatal0;

    bool refPicListModificationFlagl1 = false;
    std::vector<RefPicListModificationData> refPicListModificationDatal1;

    RefPicListModification() = default;
    explicit RefPicListModification(DecodingContext& context, BitstreamReader& reader);
};


