#pragma once
#include <IO/BitstreamReader.h>


struct GridPosView
{
    std::uint8_t gridPosViewId = 0;
    std::int8_t gridPosX;
    std::int8_t gridPosY;

    GridPosView() = default;
    explicit GridPosView(BitstreamReader& reader)
    {
        gridPosViewId = reader.readExpoGlomb();
        gridPosX = reader.readSignedExpoGlomb();
        gridPosY = reader.readSignedExpoGlomb();
    }
};

