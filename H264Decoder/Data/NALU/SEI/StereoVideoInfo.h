#pragma once
#include <IO/BitstreamReader.h>


struct StereoVideoInfo
{
    bool fieldViewsFlag = false;
    bool topFieldIsLeftViewFlag = false;
    bool currentFrameIsLeftViewFlag = false;
    bool nextFrameIsSecondViewFlag = false;

    bool leftViewSelfContainedFlag = false;
    bool rightViewSelfContainedFLag = false;

    StereoVideoInfo() = default;
    explicit StereoVideoInfo(BitstreamReader& reader)
    {
        fieldViewsFlag = reader.readBits<bool, 1>();
        if (fieldViewsFlag)
        {
            topFieldIsLeftViewFlag = reader.readBits<bool, 1>();
        }
        else
        {
            currentFrameIsLeftViewFlag = reader.readBits<bool, 1>();
            nextFrameIsSecondViewFlag = reader.readBits<bool, 1>();
        }
        leftViewSelfContainedFlag = reader.readBits<bool, 1>();
        rightViewSelfContainedFLag = reader.readBits<bool, 1>();
    }
};



