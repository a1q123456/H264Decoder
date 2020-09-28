#pragma once
#include <IO/BitstreamReader.h>


struct PicTiming
{
    struct ClockTS
    {
        bool clockTimestampFlag = false;
        std::uint8_t ctType = 0;
        bool nuitFieldBasedFlag = false;
        std::uint8_t countingType = 0;
        bool fullTimestampFlag = false;
        bool discontinuityFlag = false;
        bool cntDroppedFlag = false;
        std::uint8_t nFrames = 0;

        std::uint8_t secondsValue = 0;
        std::uint8_t minutesValue = 0;
        std::uint8_t hoursValue = 0;

        bool secondsFlag = false;
        bool minutesFlag = false;
        bool hoursFlag = false;

        std::int16_t timeOffset;
    };

    std::uint16_t cpbRemovalDelay = 0;
    std::uint16_t dpbOutputDelay = 0;

    std::uint8_t picStruct = 0;
    std::vector<ClockTS> clockTSs;

    PicTiming() = default;
    explicit PicTiming(DecodingContext& context, BitstreamReader& reader, int payloadSize)
    {
        auto cpbDpbDelaysPresentFlag = context.currentSPS().vuiParameters.nalHrdParametersPresentFlag ||
            context.currentSPS().vuiParameters.vclHrdParametersPresentFlag ||
            context.applicationDeterminedValues.cpbDpbDelaysPresentFlag;

        if (cpbDpbDelaysPresentFlag)
        {
            cpbRemovalDelay = reader.readBits<std::uint16_t>(context.currentSPS().vuiParameters.hrdParameters.cpbRemovalDelayLengthMinus1 + 1);
            dpbOutputDelay = reader.readBits<std::uint16_t>(context.currentSPS().vuiParameters.hrdParameters.dpbOutputDelayLengthMinus1 + 1);
        }
    }

};


