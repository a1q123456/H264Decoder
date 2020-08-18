#pragma once
#include <cstdint>
#include <IO/BitstreamReader.h>

struct NALUnitHeader3DavcExtension
{
    std::uint8_t viewIdx = 0;
    bool depthFlag = false;
    bool nonIDRFlag = false;
    std::uint8_t temporalId = 0;
    bool anchorPicFlag = false;
    bool interViewFlag = false;

    NALUnitHeader3DavcExtension() = default;
    explicit NALUnitHeader3DavcExtension(BitstreamReader& reader)
    {
        viewIdx = reader.readBits<std::uint8_t, 8>();
        depthFlag = reader.readBits<std::uint8_t, 1>();
        nonIDRFlag = reader.readBits<std::uint8_t, 1>();
        temporalId = reader.readBits<std::uint8_t, 3>();
        anchorPicFlag = reader.readBits<std::uint8_t, 1>();
        interViewFlag = reader.readBits<std::uint8_t, 1>();
    }
};

