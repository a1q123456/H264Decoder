#pragma once
#include <IO/BitstreamReader.h>


struct ContentLightLevelInfo
{
    std::uint16_t maxContentLightLevel = 0;
    std::uint16_t maxPicAverageLightLevel = 0;

    ContentLightLevelInfo() = default;
    explicit ContentLightLevelInfo(BitstreamReader& reader)
    {
        maxContentLightLevel = reader.readBits<std::uint16_t, 16>();
        maxPicAverageLightLevel = reader.readBits<std::uint16_t, 16>();
    }
};


