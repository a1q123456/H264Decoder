#pragma once
#include <IO/BitstreamReader.h>
#include "HrdParameters.h"
#include <Data\NALU\VuiTimingInfo.h>


struct VuiExtInfo
{
    std::uint8_t vuiExtDependencyId = 0;
    std::uint8_t vuiExtQualityId = 0;
    std::uint8_t vuiExtTemporalId = 0;
    bool vuiExtTimingInfoPresentFlag = false;
    VuiTimingInfo vuiExtTimingInfo;

    bool vuiExtNalHrdParametersPresentFlag = false;
    HrdParameters nalHrdParameters;

    bool vuiExtVclHrdParamtersPresentFlag = false;
    HrdParameters vclHrdParameters;
    bool vuiExtLowDelayHrdFlag = false;
    bool vuiExtPicStructPresentFlag = false;

    VuiExtInfo() = default;
    explicit VuiExtInfo(BitstreamReader& reader)
    {
        vuiExtDependencyId = reader.readBits<std::uint8_t, 3>();
        vuiExtQualityId = reader.readBits<std::uint8_t, 4>();
        vuiExtTemporalId = reader.readBits<std::uint8_t, 3>();
        vuiExtTimingInfoPresentFlag = reader.readBits<std::uint8_t, 1>();
        if (vuiExtTimingInfoPresentFlag)
        {
            vuiExtTimingInfo = VuiTimingInfo{ reader };
        }
        vuiExtNalHrdParametersPresentFlag = reader.readBits<std::uint8_t, 1>();
        if (vuiExtNalHrdParametersPresentFlag)
        {
            nalHrdParameters = HrdParameters{ reader };
        }

        vuiExtVclHrdParamtersPresentFlag = reader.readBits<std::uint8_t, 1>();
        if (vuiExtVclHrdParamtersPresentFlag)
        {
            vclHrdParameters = HrdParameters{ reader };
        }

        if (vuiExtNalHrdParametersPresentFlag || vuiExtVclHrdParamtersPresentFlag)
        {
            vuiExtLowDelayHrdFlag = reader.readBits<std::uint8_t, 1>();
        }
        vuiExtPicStructPresentFlag = reader.readBits<std::uint8_t, 1>();
    }
};

