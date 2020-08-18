#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\SpsMvcdApplicableOp.h>


struct SpsMvcdLevelValuesSignalled
{
    std::uint8_t levelIdc = 0;
    std::uint8_t numApplicableOpsMinus1 = 0;
    std::vector<SpsMvcdApplicableOp> spsMvcdApplicableOps;

    SpsMvcdLevelValuesSignalled() = default;
    explicit SpsMvcdLevelValuesSignalled(BitstreamReader& reader)
    {
        levelIdc = reader.readBits<std::uint8_t, 8>();
        numApplicableOpsMinus1 = reader.readExpoGlomb();
        for (auto j = 0; j < numApplicableOpsMinus1; j++)
        {
            spsMvcdApplicableOps.emplace_back(reader);
        }
    }
};


