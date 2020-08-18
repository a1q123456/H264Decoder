#pragma once
#include <IO/BitstreamReader.h>


struct PostFilterHint
{
    std::uint8_t filterHintSizeY = 0;
    std::uint8_t filterHintSizeX = 0;
    std::uint8_t filterHintType = 0;
    std::vector<std::vector<std::int16_t>> filterHints[3];
    bool additionalExtensionFlag = false;

    PostFilterHint() = default;
    explicit PostFilterHint(BitstreamReader& reader)
    {
        filterHintSizeY = reader.readExpoGlomb();
        filterHintSizeX = reader.readExpoGlomb();
        filterHintType = reader.readBits<std::uint8_t, 2>();
        for (auto colourComponent = 0; colourComponent < 3; colourComponent++)
        {
            for (auto cy = 0; cy < filterHintSizeY; cy++)
            {
                for (auto cx = 0; cx < filterHintSizeX; cx++)
                {
                    filterHints[colourComponent][cy][cx] = reader.readSignedExpoGlomb();
                }
            }
        }
        additionalExtensionFlag = reader.readBits<bool, 1>();
    }
};


