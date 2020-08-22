#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\RefPicListMvcModificationData.h>


struct RefPicListMvcModification
{
    bool refPicListModificationFlagl0 = false;
    std::vector<RefPicListMvcModificationData> datal0;

    bool refPicListModificationFlagl1 = false;
    std::vector<RefPicListMvcModificationData> datal1;
};


