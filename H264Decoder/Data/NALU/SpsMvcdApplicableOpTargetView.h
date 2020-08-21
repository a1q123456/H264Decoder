#pragma once
#include <IO/BitstreamReader.h>


struct SpsMvcdApplicableOpTargetView
{
    std::uint16_t applicableOpTargetViewId = 0;
    bool applicableOpDepthFlag = false;
    bool applicableOpTextureFlag = false;

    SpsMvcdApplicableOpTargetView() = default;
    explicit SpsMvcdApplicableOpTargetView(BitstreamReader& reader)
    {
        applicableOpTargetViewId = reader.readExpoGlomb();
        applicableOpDepthFlag = reader.readBits<std::uint8_t, 1>();
        applicableOpTextureFlag = reader.readBits<std::uint8_t, 1>();
    }

};


