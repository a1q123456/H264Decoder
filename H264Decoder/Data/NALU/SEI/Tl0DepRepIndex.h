#pragma once
#include <IO/BitstreamReader.h>


struct Tl0DepRepIndex
{
    std::uint8_t tl0DepRepIdx = 0;
    std::uint16_t effectiveIdrPicId = 0;

    Tl0DepRepIndex() = default;
    explicit Tl0DepRepIndex(BitstreamReader& reader)
    {
        tl0DepRepIdx = reader.readBits<std::uint8_t, 8>();
        effectiveIdrPicId = reader.readBits<std::uint16_t, 16>();
    }
};



