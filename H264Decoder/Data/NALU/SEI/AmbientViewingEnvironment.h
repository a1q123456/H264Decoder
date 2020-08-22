#pragma once
#include <IO/BitstreamReader.h>

struct AmbientViewingEnvironment
{
    std::uint32_t ambientIlluminance = 0;
    std::uint16_t ambientLightX = 0;
    std::uint16_t ambientLightY = 0;

    AmbientViewingEnvironment() = default;
    explicit AmbientViewingEnvironment(BitstreamReader& reader)
    {
        ambientIlluminance = reader.readBits<std::uint32_t, 32>();
        ambientLightX = reader.readBits<std::uint16_t, 16>();
        ambientLightY = reader.readBits<std::uint16_t, 16>();

    }
};


