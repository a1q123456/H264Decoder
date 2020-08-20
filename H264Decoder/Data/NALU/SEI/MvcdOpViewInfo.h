#pragma once
#include <IO/BitstreamReader.h>


struct MvcdOpViewInfo
{
    bool viewInfoDepthViewPresentFlag = false;
    bool mvcdDepthViewFlag = false;
    bool viewInfoTextureViewPresentFlag = false;
    bool mvcdTextureViewFlag = false;

    MvcdOpViewInfo() = default;
    explicit MvcdOpViewInfo(BitstreamReader& reader)
    {
        viewInfoDepthViewPresentFlag = reader.readBits<bool, 1>();
        if (viewInfoDepthViewPresentFlag)
        {
            mvcdDepthViewFlag = reader.readBits<bool, 1>();
        }
        viewInfoTextureViewPresentFlag = reader.readBits<bool, 1>();
        if (viewInfoTextureViewPresentFlag)
        {
            mvcdTextureViewFlag = reader.readBits<bool, 1>();
        }
    }
};


