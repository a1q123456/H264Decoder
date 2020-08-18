#pragma once
#include <IO/BitstreamReader.h>


struct SubSeqInfo
{
    std::uint8_t subSeqLayerNum = 0;
    std::uint8_t subSeqId = 0;

    bool firstRefPicFlag = false;
    bool leadingNonRefPicFlag = false;
    bool lastPicFlag = false;
    bool subSeqFrameNumFlag = false;

    std::uint8_t subSeqFrameNum = 0;

    SubSeqInfo() = default;
    explicit SubSeqInfo(BitstreamReader& reader)
    {
        subSeqLayerNum = reader.readExpoGlomb();
        subSeqId = reader.readExpoGlomb();

        firstRefPicFlag = reader.readBits<bool, 1>();
        leadingNonRefPicFlag = reader.readBits<bool, 1>();
        lastPicFlag = reader.readBits<bool, 1>();
        subSeqFrameNumFlag = reader.readBits<bool, 1>();
        if (subSeqFrameNumFlag)
        {
            subSeqFrameNum = reader.readExpoGlomb();
        }
    }
};


