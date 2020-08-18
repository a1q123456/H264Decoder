#pragma once
#include <IO/BitstreamReader.h>

struct NALUnitHeaderMvcExtension
{
    bool nonIDRFlag = false;
    std::uint8_t priofityId = 0;
    std::uint16_t viewId = 0;
    std::uint8_t temporalId = 0;
    bool anchorPicFlag = false;
    bool interViewFlag = false;
    std::uint8_t reservedOneBit = 0;

    NALUnitHeaderMvcExtension() = default;
    explicit NALUnitHeaderMvcExtension(BitstreamReader& reader)
    {
        nonIDRFlag = reader.readBits<std::uint8_t, 1>();
        priofityId = reader.readBits<std::uint8_t, 6>();
        viewId = reader.readBits<std::uint16_t, 10>();
        temporalId = reader.readBits<std::uint8_t, 3>();
        anchorPicFlag = reader.readBits<std::uint8_t, 1>();
        interViewFlag = reader.readBits<std::uint8_t, 1>();
        reservedOneBit = reader.readBits<std::uint8_t, 1>();
    }
};

