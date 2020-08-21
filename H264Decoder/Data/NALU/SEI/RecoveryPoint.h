#pragma once
#include <IO/BitstreamReader.h>


struct RecoveryPoint
{
    std::uint16_t recoveryFrameCnt = 0;
    bool exactMatchFlag = false;
    bool brokenLinkFlag = false;
    std::uint8_t changingSliceGroupIdc = 0;

    RecoveryPoint() = default;
    explicit RecoveryPoint(BitstreamReader& reader)
    {
        recoveryFrameCnt = reader.readExpoGlomb();
        exactMatchFlag = reader.readBits<bool, 1>();
        brokenLinkFlag = reader.readBits<bool, 1>();
        changingSliceGroupIdc = reader.readBits<std::uint8_t, 2>();
    }
};


