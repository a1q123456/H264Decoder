#pragma once
#include <IO/BitstreamReader.h>


struct SpsMvcApplicableOps
{
    std::uint8_t applicableOpTemproalId = 0;
    std::uint8_t applicableOpNumTargetViewsMinus1 = 0;
    std::vector<std::uint8_t> applicableOpTargetViewIds;
    std::uint8_t applicableOpNumViewsMinus1 = 0;

    SpsMvcApplicableOps() = default;
    explicit SpsMvcApplicableOps(BitstreamReader& reader)
    {
        applicableOpTemproalId = reader.readBits<std::uint8_t, 3>();
        applicableOpNumTargetViewsMinus1 = reader.readExpoGlomb();
        for (auto k = 0; k <= applicableOpNumTargetViewsMinus1; k++)
        {
            applicableOpTargetViewIds.push_back(reader.readExpoGlomb());
        }
        applicableOpNumViewsMinus1 = reader.readExpoGlomb();
    }
};


