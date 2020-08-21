#pragma once
#include <IO/BitstreamReader.h>


struct DisplayOrientation
{
    bool displayOrientationCancelFlag = false;

    bool horFlip = false;
    bool verFlip = false;

    std::uint16_t anticlockwiseRotation = 0;
    std::uint16_t displayOrientationRepetitionPeriod = 0;
    bool displayOrientationExtensionFlag = false;

    DisplayOrientation() = default;
    explicit DisplayOrientation(BitstreamReader& reader)
    {
        displayOrientationCancelFlag = reader.readBits<bool, 1>();
        if (!displayOrientationCancelFlag)
        {
            horFlip = reader.readBits<bool, 1>();
            verFlip = reader.readBits<bool, 1>();
            anticlockwiseRotation = reader.readBits<std::uint16_t, 16>();
            displayOrientationRepetitionPeriod = reader.readExpoGlomb();
            displayOrientationExtensionFlag = reader.readBits<bool, 1>();
        }
    }
};


