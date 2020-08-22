#include "pch.h"
#include "RecoveryPoint.h"

RecoveryPoint::RecoveryPoint(BitstreamReader& reader)
{
    recoveryFrameCnt = reader.readExpoGlomb();
    exactMatchFlag = reader.readBits<bool, 1>();
    brokenLinkFlag = reader.readBits<bool, 1>();
    changingSliceGroupIdc = reader.readBits<std::uint8_t, 2>();
}
