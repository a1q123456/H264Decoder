#pragma once
#include <IO/BitstreamReader.h>


struct FrameCropping
{
    std::uint8_t frameCropLeftOffset = 0;
    std::uint8_t frameCropRightOffset = 0;
    std::uint8_t frameCropTopOffset = 0;
    std::uint8_t frameCropBottomOffset = 0;

    FrameCropping() = default;
    explicit FrameCropping(BitstreamReader& rbspReader)
    {
        frameCropLeftOffset = rbspReader.readExpoGlomb();
        frameCropRightOffset = rbspReader.readExpoGlomb();
        frameCropTopOffset = rbspReader.readExpoGlomb();
        frameCropBottomOffset = rbspReader.readExpoGlomb();
    }
};

