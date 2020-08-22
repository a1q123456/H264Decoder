#pragma once
#include <IO/BitstreamReader.h>


struct RecoveryPoint
{
    std::uint16_t recoveryFrameCnt = 0;
    bool exactMatchFlag = false;
    bool brokenLinkFlag = false;
    std::uint8_t changingSliceGroupIdc = 0;

    RecoveryPoint() = default;
    explicit RecoveryPoint(BitstreamReader& reader);
};


