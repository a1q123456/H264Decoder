#pragma once
#include <IO/BitstreamReader.h>

struct RbspTrailingBits
{
    std::uint8_t rbspStopOneBit = 0;
    std::uint8_t rbspAlignmentZeroBits = 0;

    RbspTrailingBits() = default;
    RbspTrailingBits(BitstreamReader& reader)
    {
        rbspStopOneBit = reader.readBits<std::uint8_t, 1>();
        if (rbspStopOneBit != 1)
        {
            throw std::runtime_error("error trailing bits");
        }
        while (!reader.byteAligned())
        {
            reader.readBits<std::uint64_t>(1);
        }
    }
};


