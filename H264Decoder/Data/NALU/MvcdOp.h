#pragma once
#include <IO/BitstreamReader.h>


struct MvcdOp
{
    std::uint8_t vuiMvcdTemporalId = 0;
    std::uint8_t vuiMvcdNumTargetOutputViewsMinus1 = 0;
    std::vector<VuiView> targetOutputViews;

    bool vuiMvcdTimingInfoPresentFlag = false;
    VuiTimingInfo timingInfo;

    bool vuiMvcdNalHrdParameterPresentFlag = false;
    HrdParameters mvcdNalHrdParameter;

    bool vuiMvcdVclHrdParameterPresentFlag = false;
    HrdParameters mvcdVclHrdParameter;

    bool vuiMvcdLowDelayHrdFlag = false;
    bool vuiMvcdPicStructPresentFlag = false;

    MvcdOp() = default;
    explicit MvcdOp(BitstreamReader& reader)
    {
        vuiMvcdTemporalId = reader.readBits<std::uint8_t, 3>();
        vuiMvcdNumTargetOutputViewsMinus1 = reader.readExpoGlomb();
        for (auto j = 0; j <= vuiMvcdNumTargetOutputViewsMinus1; j++)
        {
            VuiView view;
            view.viewId = reader.readExpoGlomb();
            view.depthViewPresentFlag = reader.readBits<std::uint8_t, 1>();
            view.textureViewPresentFlag = reader.readBits<std::uint8_t, 1>();
            targetOutputViews.emplace_back(view);
        }
        vuiMvcdTimingInfoPresentFlag = reader.readBits<std::uint8_t, 1>();
        if (vuiMvcdTimingInfoPresentFlag)
        {
            timingInfo = VuiTimingInfo{ reader };
        }
        vuiMvcdNalHrdParameterPresentFlag = reader.readBits<std::uint8_t, 1>();
        mvcdNalHrdParameter = HrdParameters{ reader };
        vuiMvcdVclHrdParameterPresentFlag = reader.readBits<std::uint8_t, 1>();
        mvcdVclHrdParameter = HrdParameters{ reader };

        if (vuiMvcdNalHrdParameterPresentFlag || vuiMvcdVclHrdParameterPresentFlag)
        {
            vuiMvcdLowDelayHrdFlag = reader.readBits<std::uint8_t, 1>();
        }
        vuiMvcdPicStructPresentFlag = reader.readBits<std::uint8_t, 1>();
    }
};

