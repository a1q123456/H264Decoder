#pragma once
#include <IO/BitstreamReader.h>

struct SubSeqCharacteristics
{
    struct ReferencedSubSeq
    {
        std::uint16_t refSubSeqLayerNum = 0;
        std::uint16_t refSubSeqId = 0;
        std::uint8_t refSubSeqDirection = 0;
    };
    std::uint16_t subSeqLayerNum = 0;
    std::uint16_t subSeqId = 0;
    bool durationFlag = false;
    std::uint32_t subSeqDuration = 0;
    bool averageRateFlag = false;
    bool accurateStatisticFlag = false;
    std::uint16_t averageBitRate = 0;
    std::uint16_t averageFrameRate = 0;

    std::uint16_t numReferencedSubSeqs = 0;
    std::vector<ReferencedSubSeq> referencedSubSeqs;

    SubSeqCharacteristics() = default;
    explicit SubSeqCharacteristics(BitstreamReader& reader)
    {
        subSeqLayerNum = reader.readExpoGlomb();
        subSeqId = reader.readExpoGlomb();
        durationFlag = reader.readBits<bool, 1>();
        if (durationFlag)
        {
            subSeqDuration = reader.readBits<std::uint32_t, 32>();
        }
        bool averageRateFlag = reader.readBits<bool, 1>();
        if (averageRateFlag)
        {
            accurateStatisticFlag = reader.readBits<bool, 1>();
            averageBitRate = reader.readBits<std::uint16_t, 16>();
            averageFrameRate = reader.readBits<std::uint16_t, 16>();
        }

        numReferencedSubSeqs = reader.readExpoGlomb();
        for (auto n = 0; n < numReferencedSubSeqs; n++)
        {
            ReferencedSubSeq rss;
            rss.refSubSeqLayerNum = reader.readExpoGlomb();
            rss.refSubSeqId = reader.readExpoGlomb();
            rss.refSubSeqDirection = reader.readBits<std::uint8_t, 1>();
        }
    }
};
