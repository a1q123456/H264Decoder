#pragma once
#include <IO/BitstreamReader.h>


struct AlternativeTransferCharacteristics
{
    std::uint8_t preferredTransferCharacateristics = 0;

    AlternativeTransferCharacteristics() = default;
    explicit AlternativeTransferCharacteristics(BitstreamReader& reader)
    {
        preferredTransferCharacateristics = reader.readBits<std::uint8_t, 8>();
    }
};


