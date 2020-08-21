#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\SpsMvcApplicableOps.h>


struct SpsMvcLevelValuesSignalled
{
    std::uint8_t levelIdc = 0;
    std::uint16_t numApplicableOpsMinus1 = 0;
    std::vector<SpsMvcApplicableOps> applicableOps;

    SpsMvcLevelValuesSignalled() = default;
    explicit SpsMvcLevelValuesSignalled(BitstreamReader& reader)
    {
        levelIdc = reader.readBits<std::uint8_t, 8>();
        numApplicableOpsMinus1 = reader.readExpoGlomb();
        for (auto j = 0; j <= numApplicableOpsMinus1; j++)
        {
            applicableOps.emplace_back(reader);
        }
    }

};


