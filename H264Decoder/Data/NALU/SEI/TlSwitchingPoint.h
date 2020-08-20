#pragma once
#include <IO/BitstreamReader.h>


struct TlSwitchingPoint
{
    std::int32_t deltaFrameNum = 0;

    TlSwitchingPoint() = default;
    explicit TlSwitchingPoint(BitstreamReader& reader)
    {
        deltaFrameNum = reader.readSignedExpoGlomb();
    }
};


