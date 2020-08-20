#pragma once
#include <IO/BitstreamReader.h>


struct DirectlyDependentView
{
    std::uint32_t viewId = 0;
    MvcdOpViewInfo mvcdOpViewInfo;

    DirectlyDependentView() = default;
    explicit DirectlyDependentView(BitstreamReader& reader, bool isMvcd)
    {
        viewId = reader.readExpoGlomb();
        if (isMvcd)
        {
            mvcdOpViewInfo = MvcdOpViewInfo{ reader };
        }
    }
};


