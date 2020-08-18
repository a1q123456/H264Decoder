#pragma once
#include <IO/BitstreamReader.h>


struct FilmGrainCharacteristics
{
    struct CompModel
    {
        struct IntensityInterval
        {
            std::uint8_t intensityIntervalLowerBound = 0;
            std::uint8_t intensityIntervalUpperBound = 0;
            std::vector<std::int16_t> compModelValue;
        };

        std::uint8_t numIntensityIntervalsMinus1 = 0;
        std::uint8_t numModelValuesMinus1 = 0;
        std::vector<IntensityInterval> intensityIntervals;
    };

    bool filmGrainCharacteristicsCancelFlag = false;
    std::uint8_t filmGrainModelId = 0;
    bool separateColourDescriptionPresentFlag = false;
    std::uint8_t filmGrainBitDepthLumaMinus8 = 0;
    std::uint8_t filmGrainBitDepthChromaMinus8 = 0;
    bool filmGrainFullRangeFlag = false;
    std::uint8_t filmGrainColourPrimaries = 0;
    std::uint8_t filmGrainTransferCharacteristics = 0;
    std::uint8_t filmGrainMatrixCoefficients = 0;

    std::uint8_t blendingModeId = 0;
    std::uint8_t log2ScaleFactor = 0;
    bool compModelPresentFlag[3] = { 0 };
    CompModel compModels[3]{};
    std::uint8_t filmGrainCharacteristicsRepetitionPreiod = 0;

    FilmGrainCharacteristics() = default;
    explicit FilmGrainCharacteristics(BitstreamReader& reader)
    {
        filmGrainCharacteristicsCancelFlag = reader.readBits<bool, 1>();
        if (!filmGrainCharacteristicsCancelFlag)
        {
            filmGrainModelId = reader.readBits<std::uint8_t, 2>();
            separateColourDescriptionPresentFlag = reader.readBits<bool, 1>();
            if (separateColourDescriptionPresentFlag)
            {
                filmGrainBitDepthChromaMinus8 = reader.readBits<std::uint8_t, 3>();
                filmGrainBitDepthChromaMinus8 = reader.readBits<std::uint8_t, 3>();
                filmGrainFullRangeFlag = reader.readBits<bool, 1>();
                filmGrainColourPrimaries = reader.readBits<std::uint8_t, 8>();
                filmGrainTransferCharacteristics = reader.readBits<std::uint8_t, 8>();
                filmGrainMatrixCoefficients = reader.readBits<std::uint8_t, 8>();
            }
            blendingModeId = reader.readBits<std::uint8_t, 2>();
            log2ScaleFactor = reader.readBits<std::uint8_t, 4>();
            for (auto c = 0; c < 3; c++)
            {
                compModelPresentFlag[c] = reader.readBits<bool, 1>();
            }
            for (auto c = 0; c < 3; c++)
            {
                if (compModelPresentFlag[c])
                {
                    compModels[c].numIntensityIntervalsMinus1 = reader.readBits<std::uint8_t, 8>();
                    compModels[c].numModelValuesMinus1 = reader.readBits<std::uint8_t, 8>();
                    for (auto i = 0; i <= compModels[c].numIntensityIntervalsMinus1; i++)
                    {
                        compModels[c].intensityIntervals[i].intensityIntervalLowerBound = reader.readBits<std::uint8_t, 8>();
                        compModels[c].intensityIntervals[i].intensityIntervalUpperBound = reader.readBits<std::uint8_t, 8>();
                        for (auto j = 0; j <= compModels[c].numModelValuesMinus1; j++)
                        {
                            compModels[c].intensityIntervals[i].compModelValue[j] = reader.readSignedExpoGlomb();
                        }
                    }
                }
            }
            filmGrainCharacteristicsRepetitionPreiod = reader.readExpoGlomb();
        }
    }
};


