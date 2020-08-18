#pragma once
#include <IO/BitstreamReader.h>


struct VuiView
{
    std::uint8_t viewId = 0;
    std::uint8_t depthViewId = 0;
    bool depthViewPresentFlag = false;
    bool textureViewPresentFlag = false;

    VuiView() = default;
};


