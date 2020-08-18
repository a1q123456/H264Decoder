#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\SpsMvcdApplicableOpTargetView.h>


struct SpsMvcdApplicableOp
{
    std::uint8_t applicableOpTemporalId = 0;
    std::uint8_t applicableOpNumTargetViewsMinus1 = 0;
    std::vector<SpsMvcdApplicableOpTargetView> targetViews;

    std::uint8_t applicableOpNumTextureViewsMinus1 = 0;
    std::uint8_t applicableOpNumDepthViews = 0;

    SpsMvcdApplicableOp() = default;
    explicit SpsMvcdApplicableOp(BitstreamReader& reader)
    {
        applicableOpTemporalId = reader.readBits<std::uint8_t, 3>();
        applicableOpNumTargetViewsMinus1 = reader.readExpoGlomb();
        for (auto k = 0; k <= applicableOpNumTargetViewsMinus1; k++)
        {
            targetViews.emplace_back(reader);
        }
        applicableOpNumTextureViewsMinus1 = reader.readExpoGlomb();
        applicableOpNumDepthViews = reader.readExpoGlomb();
    }
};

