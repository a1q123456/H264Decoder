#pragma once
#include <IO/BitstreamReader.h>


struct BaseViewTemporalHrd
{
    struct TemporalLayer
    {
        std::uint8_t seiMvcTemporalId = 0;
        bool seiMvcTimingInfoPresentFlag = false;
        std::uint32_t seiMvcNumUnitsInTick = 0;
        std::uint32_t seiMvcTimeScale = 0;
        bool seiMvcFixedFrameRateFlag = false;

        bool seiMvcNalHrdParametersPresentFlag = false;
        bool seiMvcVclHrdParametersPresentFlag = false;

        HrdParameters hrdParameters;
        bool seiMvcLowDelayHrdFlag = false;
        bool seiMvcPicStructPresentFlag = false;

        TemporalLayer() = default;
        explicit TemporalLayer(BitstreamReader& reader)
        {
            seiMvcTemporalId = reader.readBits<std::uint8_t, 3>();
            seiMvcTimingInfoPresentFlag = reader.readBits<bool, 1>();
            if (seiMvcTimingInfoPresentFlag)
            {
                seiMvcNumUnitsInTick = reader.readBits<std::uint32_t, 32>();
                seiMvcTimeScale = reader.readBits<std::uint32_t, 32>();
                seiMvcFixedFrameRateFlag = reader.readBits<bool, 1>();
            }
            seiMvcNalHrdParametersPresentFlag = reader.readBits<bool, 1>();
            if (seiMvcNalHrdParametersPresentFlag)
            {
                hrdParameters = HrdParameters{ reader };
            }
            seiMvcVclHrdParametersPresentFlag = reader.readBits<bool, 1>();
            if (seiMvcVclHrdParametersPresentFlag)
            {
                hrdParameters = HrdParameters{ reader };
            }
            if (seiMvcNalHrdParametersPresentFlag || seiMvcVclHrdParametersPresentFlag)
            {
                seiMvcLowDelayHrdFlag = reader.readBits<bool, 1>();
            }
            seiMvcPicStructPresentFlag = reader.readBits<bool, 1>();
        }
    };

    std::uint32_t numOfTemporalLayersInBaseViewMinus1 = 0;
    std::vector<TemporalLayer> temporalLayersInBaseView;

    BaseViewTemporalHrd() = default;
    explicit BaseViewTemporalHrd(BitstreamReader& reader)
    {
        numOfTemporalLayersInBaseViewMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= numOfTemporalLayersInBaseViewMinus1; i++)
        {
            temporalLayersInBaseView.emplace_back(reader);
        }
    }
};


