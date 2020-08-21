#pragma once
#include <IO/BitstreamReader.h>


struct ToneMappingInfo
{
    struct Pivot
    {
        std::uint16_t codedPivotValue = 0;
        std::uint16_t targetPivotValue = 0;
    };

    std::uint16_t toneMapId = 0;
    bool toneMapCancelFlag = false;
    std::uint16_t toneMapRepetitionPeriod = 0;
    std::uint8_t codedDataBitDepth = 0;
    std::uint8_t targetBitDepth = 0;
    std::uint16_t toneMapModelId = 0;
    std::uint32_t minValue = 0;
    std::uint32_t maxValue = 0;

    std::uint32_t sigmoidMidpoint = 0;
    std::uint32_t sigmoidWidth = 0;
    std::vector<std::uint16_t> startOfCodedIntervals;

    std::uint16_t numPivots = 0;
    std::vector<Pivot> pivots;

    std::uint8_t cameraIsoSpeedIdc = 0;
    std::uint32_t cameraIsoSpeedValue = 0;
    std::uint8_t exposureIndexIdc = 0;
    std::uint32_t exposureIndexValue = 0;
    bool exposureCompensationValueSignFlag = false;
    std::uint16_t exposureCompensationValueNumerator = 0;
    std::uint16_t exposureCompensationValueDenomIdc = 0;

    std::uint32_t refScreenLuminanceWhite = 0;
    std::uint32_t extendedRangeWhiteLevel = 0;

    std::uint16_t nominalBlackLevelLumaCodeValue = 0;
    std::uint16_t nominalWhiteLevelLumaCodeValue = 0;
    std::uint16_t extendedWhiteLevelLumaCodeValue = 0;

    ToneMappingInfo() = default;
    explicit ToneMappingInfo(BitstreamReader& reader)
    {
        toneMapId = reader.readExpoGlomb();
        toneMapCancelFlag = reader.readBits<bool, 1>();
        if (!toneMapCancelFlag)
        {
            toneMapRepetitionPeriod = reader.readExpoGlomb();
            codedDataBitDepth = reader.readBits<std::uint8_t, 8>();
            targetBitDepth = reader.readBits<std::uint8_t, 8>();
            toneMapModelId = reader.readExpoGlomb();
            if (toneMapModelId == 0)
            {
                minValue = reader.readBits<std::uint32_t, 32>();
                maxValue = reader.readBits<std::uint32_t, 32>();
            }
            if (toneMapModelId == 1)
            {
                sigmoidMidpoint = reader.readBits<std::uint32_t, 32>();
                sigmoidWidth = reader.readBits<std::uint32_t, 32>();
            }
            if (toneMapModelId == 2)
            {
                for (auto i = 0; i < (1 << targetBitDepth); i++)
                {
                    startOfCodedIntervals.emplace_back(reader.readBits<std::uint16_t>(((codedDataBitDepth + 7) >> 3) << 3));
                }
            }
            if (toneMapModelId == 3)
            {
                numPivots = reader.readBits<std::uint16_t, 16>();
                for (auto i = 0; i < numPivots; i++)
                {
                    Pivot p;
                    p.codedPivotValue = reader.readBits<std::uint16_t>(((codedDataBitDepth + 7) >> 3) << 3);
                    p.targetPivotValue = reader.readBits<std::uint16_t>(((targetBitDepth + 7) >> 3) << 3);
                    pivots.emplace_back(p);
                }
            }
            if (toneMapModelId == 4)
            {
                cameraIsoSpeedIdc = reader.readBits<std::uint8_t, 8>();
                if (cameraIsoSpeedIdc == Extended_ISO)
                {
                    cameraIsoSpeedValue = reader.readBits<std::uint32_t, 32>();
                }
                exposureIndexIdc = reader.readBits<std::uint8_t, 8>();
                if (exposureIndexIdc == Extended_ISO)
                {
                    exposureIndexValue = reader.readBits<std::uint32_t, 32>();
                }
                exposureCompensationValueSignFlag = reader.readBits<bool, 1>();
                exposureCompensationValueNumerator = reader.readBits<std::uint16_t, 16>();
                exposureCompensationValueDenomIdc = reader.readBits<std::uint16_t, 16>();
                refScreenLuminanceWhite = reader.readBits<std::uint32_t, 32>();
                extendedRangeWhiteLevel = reader.readBits<std::uint32_t, 32>();
                nominalBlackLevelLumaCodeValue = reader.readBits<std::uint16_t, 16>();
                nominalWhiteLevelLumaCodeValue = reader.readBits<std::uint16_t, 16>();
                extendedWhiteLevelLumaCodeValue = reader.readBits<std::uint16_t, 16>();
            }
        }
    }
};



