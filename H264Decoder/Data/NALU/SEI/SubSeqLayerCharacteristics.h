#pragma once
#include <IO/BitstreamReader.h>


struct SubSeqLayerCharacteristics
{
    std::uint16_t numSubSeqLayersMinus1 = 0;
    struct Data
    {

        bool accurateStatisticsFlag = false;
        std::uint16_t averageBitRate = 0;
        std::uint16_t averageFrameRate = 0;
    };

    SubSeqLayerCharacteristics() = default;
    explicit SubSeqLayerCharacteristics(BitstreamReader& reader)
    {
        numSubSeqLayersMinus1 = reader.readExpoGlomb();
        for (auto layer = 0; layer <= numSubSeqLayersMinus1; layer++)
        {
            Data data;
            data.accurateStatisticsFlag = reader.readBits<bool, 1>();
            data.averageBitRate = reader.readBits<std::uint16_t, 16>();
            data.averageFrameRate = reader.readBits<std::uint16_t, 16>();
        }
    }
};


