#pragma once
#include <IO/BitstreamReader.h>

struct VuiTimingInfo
{
    std::uint32_t vuiNumUnitsInTick = 0;
    std::uint32_t vuiTimeScale = 0;
    bool vuiFixedFrameRateFlag = false;

    VuiTimingInfo() = default;
    explicit VuiTimingInfo(BitstreamReader& reader)
    {
        vuiNumUnitsInTick = reader.readBits<std::uint32_t, 32>();
        vuiTimeScale = reader.readBits<std::uint32_t, 32>();
        vuiFixedFrameRateFlag = reader.readBits<std::uint8_t, 1>();
    }
};

