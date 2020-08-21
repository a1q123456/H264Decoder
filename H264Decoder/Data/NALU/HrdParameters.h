#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/CPB.h>

struct HrdParameters
{
    bool hasHrd = false;
    std::uint16_t cpbCntMinus1 = 0;
    std::uint8_t bitRateScale = 0;
    std::uint8_t cpbSizeScale = 0;

    std::vector<CPB> cbps;

    std::uint8_t initialCPBRemovalDelayLengthMinus1 = 0;
    std::uint8_t cpbRemovalDelayLengthMinus1 = 23;
    std::uint8_t dpbOutputDelayLengthMinus1 = 23;
    std::uint8_t timeOffsetLength = 0;

    HrdParameters() = default;

    explicit HrdParameters(BitstreamReader& rbspReader)
    {
        hasHrd = true;
        cpbCntMinus1 = rbspReader.readExpoGlomb();
        bitRateScale = rbspReader.readBits<std::uint8_t, 4>();
        cpbSizeScale = rbspReader.readBits<std::uint8_t, 4>();
        for (auto schedSelIdx = 0; schedSelIdx < cpbCntMinus1; schedSelIdx++)
        {
            cbps.emplace_back(CPB{ rbspReader.readExpoGlomb(), rbspReader.readExpoGlomb(), (bool)rbspReader.readBits<std::uint8_t, 1>() });
        }
        initialCPBRemovalDelayLengthMinus1 = rbspReader.readBits<std::uint8_t, 5>();
        cpbRemovalDelayLengthMinus1 = rbspReader.readBits<std::uint8_t, 5>();
        dpbOutputDelayLengthMinus1 = rbspReader.readBits<std::uint8_t, 5>();
        timeOffsetLength = rbspReader.readBits<std::uint8_t, 5>();
    }
};


