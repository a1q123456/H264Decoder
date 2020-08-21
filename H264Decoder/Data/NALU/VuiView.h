#pragma once
#include <IO/BitstreamReader.h>


struct VuiView
{
    std::uint16_t viewId = 0;
    std::uint16_t depthViewId = 0;
    bool depthViewPresentFlag = false;
    bool textureViewPresentFlag = false;

    VuiView() = default;
};


