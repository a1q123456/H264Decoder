#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\RefPicListModificationData.h>


struct RefPicListModification
{
    bool refPicListModificationFlagl0 = false;
    std::vector<RefPicListModificationData> refPicListModificationDatal0;

    bool refPicListModificationFlagl1 = false;
    std::vector<RefPicListModificationData> refPicListModificationDatal1;
};


