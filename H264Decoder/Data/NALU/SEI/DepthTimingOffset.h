#pragma once
#include <IO/BitstreamReader.h>


struct DepthTimingOffset
{
    std::uint8_t offsetLenMinus1 = 0;
    DecimalValue depthDispDelayOffset;

    DepthTimingOffset() = default;
    explicit DepthTimingOffset(BitstreamReader& reader)
    {
        offsetLenMinus1 = reader.readBits<std::uint8_t, 5>();
        depthDispDelayOffset.sign = 1;
        depthDispDelayOffset.fp = reader.readBits<std::uint32_t>(offsetLenMinus1 + 1);
        depthDispDelayOffset.dp = reader.readBits<std::uint8_t, 6>();
    }
};



