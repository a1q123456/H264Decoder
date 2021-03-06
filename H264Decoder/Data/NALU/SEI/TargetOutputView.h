#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/SEI/MvcdOpViewInfo.h>


struct TargetOutputView
{
    std::uint32_t viewId = 0;
    MvcdOpViewInfo mvcdOpViewInfo;

    TargetOutputView() = default;
    explicit TargetOutputView(BitstreamReader& reader, bool isMvcd)
    {
        viewId = reader.readExpoGlomb();
        if (isMvcd)
        {
            mvcdOpViewInfo = MvcdOpViewInfo{ reader };
        }
    }
};


