#pragma once
#include <IO/BitstreamReader.h>


struct MasteringDisplayColourVolume
{
    struct DisplayPrimaries
    {
        std::uint16_t displayPrimariesX = 0;
        std::uint16_t displayPrimariesY = 0;
    };

    DisplayPrimaries displayPrimaries[3]{};
    std::uint16_t whitePointX = 0;
    std::uint16_t whitePointY = 0;
    std::uint32_t maxDisplayMasteringLuminance = 0;
    std::uint32_t minDisplayMasteringLuminance = 0;

    MasteringDisplayColourVolume() = default;
    explicit MasteringDisplayColourVolume(BitstreamReader& reader)
    {
        for (auto c = 0; c < 3; c++)
        {
            displayPrimaries[c].displayPrimariesX = reader.readBits<std::uint16_t, 16>();
            displayPrimaries[c].displayPrimariesY = reader.readBits<std::uint16_t, 16>();
        }
        whitePointX = reader.readBits<std::uint16_t, 16>();
        whitePointY = reader.readBits<std::uint16_t, 16>();
        maxDisplayMasteringLuminance = reader.readBits<std::uint32_t, 32>();
        minDisplayMasteringLuminance = reader.readBits<std::uint32_t, 32>();
    }
};



