#pragma once
#include <IO/BitstreamReader.h>


struct DecRefPicMarkingRepetition
{
    bool originalIdrFlag = false;
    std::uint8_t originalFrameNum = 0;
    bool originalFieldPicFlag = false;
    bool originalBottomFieldFlag = false;

    DecRefPicMarking decRefPicMarking;

    DecRefPicMarkingRepetition() = default;
    explicit DecRefPicMarkingRepetition(DecodingContext& ctx, BitstreamReader& reader)
    {
        originalIdrFlag = reader.readBits<bool, 1>();
        originalFrameNum = reader.readExpoGlomb();

        if (ctx.currentSPS().spsData.frameMbsOnlyFlag)
        {
            originalFieldPicFlag = reader.readBits<bool, 1>();
            if (originalFieldPicFlag)
            {
                originalBottomFieldFlag = reader.readBits<bool, 1>();
            }
        }
        decRefPicMarking = DecRefPicMarking{ NaluTypes::SEI, reader };

    }
};


