#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/RbspTrailingBits.h>

struct AUDRbsp
{
    std::uint8_t primaryPicType = 0;
    RbspTrailingBits rbspTrailingBits;

    AUDRbsp() = default;
    explicit AUDRbsp(BitstreamReader& reader)
    {
        primaryPicType = reader.readBits<std::uint8_t, 8>();
        rbspTrailingBits = RbspTrailingBits{ reader };
    }
};


