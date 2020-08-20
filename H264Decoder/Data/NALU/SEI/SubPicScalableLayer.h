#pragma once
#include <IO/BitstreamReader.h>


struct SubPicScalableLayer
{
    std::uint32_t layerId = 0;

    SubPicScalableLayer() = default;
    explicit SubPicScalableLayer(BitstreamReader& reader)
    {
        layerId = reader.readExpoGlomb();
    }
};

