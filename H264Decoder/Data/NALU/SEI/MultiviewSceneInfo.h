#pragma once
#include <IO/BitstreamReader.h>


struct MultiviewSceneInfo
{
    std::uint32_t maxDisparity = 0;

    MultiviewSceneInfo() = default;
    explicit MultiviewSceneInfo(BitstreamReader& reader)
    {
        maxDisparity = reader.readExpoGlomb();
    }
};



