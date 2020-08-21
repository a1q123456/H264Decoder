#pragma once
#include <IO/BitstreamReader.h>


struct GridPosView
{
    std::uint16_t gridPosViewId = 0;
    std::int16_t gridPosX;
    std::int16_t gridPosY;

    GridPosView() = default;
    explicit GridPosView(BitstreamReader& reader)
    {
        gridPosViewId = reader.readExpoGlomb();
        gridPosX = reader.readSignedExpoGlomb();
        gridPosY = reader.readSignedExpoGlomb();
    }
};

