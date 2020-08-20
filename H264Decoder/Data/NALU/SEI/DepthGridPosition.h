#pragma once
#include <IO/BitstreamReader.h>

struct DepthGridPosition
{
    DecimalValue posX;
    DecimalValue posY;

    DepthGridPosition() = default;
    explicit DepthGridPosition(BitstreamReader& reader)
    {
        posX.fp = reader.readBits<std::uint32_t, 20>();
        posX.dp = reader.readBits<std::uint8_t, 4>();
        posX.sign = reader.readBits<std::uint8_t, 1>();

        posY.fp = reader.readBits<std::uint32_t, 20>();
        posY.dp = reader.readBits<std::uint8_t, 4>();
        posY.sign = reader.readBits<std::uint8_t, 1>();
    }
};



