#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/VuiTimingInfo.h>


struct VuiMvcOp
{
    std::uint8_t vuiMvcTemporalId = 0;
    std::uint16_t vuiMvcNumTargetOutputViewsMinus1 = 0;

    std::vector<std::uint16_t> vuiMvcViewIds;
    bool vuiMvcTimingInfoPresentFlag = false;
    VuiTimingInfo timingInfo;
    bool vuiMvcNalHrdParametersPresentFlag = false;
    HrdParameters nalHrdParameter;
    bool vuiMvcVclHrdParametersPresentFlag = false;
    HrdParameters vclHrdParameter;

    bool vuiMvcLowDelayHrdFlag = false;
    bool vuiMvcPicStructPresentFlag = false;

    VuiMvcOp() = default;
    explicit VuiMvcOp(BitstreamReader& reader)
    {
        vuiMvcTemporalId = reader.readBits<std::uint8_t, 3>();
        vuiMvcNumTargetOutputViewsMinus1 = reader.readExpoGlomb();
        for (auto j = 0; j <= vuiMvcNumTargetOutputViewsMinus1; j++)
        {
            vuiMvcViewIds.emplace_back(reader.readExpoGlomb());
        }
        vuiMvcTimingInfoPresentFlag = reader.readBits<std::uint8_t, 1>();
        if (vuiMvcTimingInfoPresentFlag)
        {
            timingInfo = VuiTimingInfo{ reader };
        }
        vuiMvcNalHrdParametersPresentFlag = reader.readBits<std::uint8_t, 1>();
        if (vuiMvcNalHrdParametersPresentFlag)
        {
            nalHrdParameter = HrdParameters{ reader };
        }
        vuiMvcVclHrdParametersPresentFlag = reader.readBits<std::uint8_t, 1>();
        if (vuiMvcVclHrdParametersPresentFlag)
        {
            vclHrdParameter = HrdParameters{ reader };
        }
        if (vuiMvcNalHrdParametersPresentFlag || vuiMvcVclHrdParametersPresentFlag)
        {
            vuiMvcLowDelayHrdFlag = reader.readBits<std::uint8_t, 1>();
        }
        vuiMvcPicStructPresentFlag = reader.readBits<std::uint8_t, 1>();
    }
};


