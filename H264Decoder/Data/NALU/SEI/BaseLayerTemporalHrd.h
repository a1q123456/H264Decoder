#pragma once
#include <IO/BitstreamReader.h>


struct BaseLayerTemporalHrd
{
    struct TemporalLayer
    {
        std::uint8_t seiTemporalId = 0;
        bool seiTimingInfoPresentFlag = false;

        std::uint32_t seiNumUnitsInTick = 0;
        std::uint32_t seiTimeScale = 0;
        bool seiFixedFrameRateFlag = false;

        bool seiNalHrdParametersPresentFlag = false;
        bool seiVclHrdParametersPresentFlag = false;

        HrdParameters hrdParameters;

        bool seiLowDelayHrdFlag = false;

        bool seiPicStructPresentFlag = false;

        TemporalLayer() = default;
        explicit TemporalLayer(BitstreamReader& reader)
        {
            seiTemporalId = reader.readBits<std::uint8_t, 3>();
            seiTimingInfoPresentFlag = reader.readBits<bool, 1>();

            if (seiTimingInfoPresentFlag)
            {
                seiNumUnitsInTick = reader.readBits<std::uint32_t, 32>();
                seiTimeScale = reader.readBits<std::uint32_t, 32>();
                seiFixedFrameRateFlag = reader.readBits<bool, 1>();
            }
            seiNalHrdParametersPresentFlag = reader.readBits<bool, 1>();
            if (seiNalHrdParametersPresentFlag)
            {
                hrdParameters = HrdParameters{ reader };
            }
            seiVclHrdParametersPresentFlag = reader.readBits<bool, 1>();
            if (seiVclHrdParametersPresentFlag)
            {
                hrdParameters = HrdParameters{ reader };
            }
            if (seiNalHrdParametersPresentFlag || seiVclHrdParametersPresentFlag)
            {
                seiLowDelayHrdFlag = reader.readBits<bool, 1>();
            }
            seiPicStructPresentFlag = reader.readBits<bool, 1>();
        }
    };

    std::uint32_t numOfTemporalLayersInBaseLayerMinus1 = 0;
    std::vector<TemporalLayer> temporalLayersInBaseLayer;

    BaseLayerTemporalHrd() = default;
    explicit BaseLayerTemporalHrd(BitstreamReader& reader)
    {
        numOfTemporalLayersInBaseLayerMinus1 = reader.readExpoGlomb();
        temporalLayersInBaseLayer.emplace_back(reader);
    }

};


