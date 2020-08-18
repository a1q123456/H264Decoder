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
        auto cpbDpbDelaysPresentFlag = context.currentSPS().spsData.vuiParameters.nalHrdParametersPresentFlag ||
            context.currentSPS().spsData.vuiParameters.vclHrdParametersPresentFlag ||
            context.applicationDeterminedValues.cpbDpbDelaysPresentFlag;

        if (cpbDpbDelaysPresentFlag)
        {
            cpbRemovalDelay = reader.readBits<std::uint16_t>(context.currentSPS().spsData.vuiParameters.hrdParameters.cpbRemovalDelayLengthMinus1 + 1);
            dpbOutputDelay = reader.readBits<std::uint16_t>(context.currentSPS().spsData.vuiParameters.hrdParameters.dpbOutputDelayLengthMinus1 + 1);
        }
        if (context.currentSPS().spsData.vuiParameters.picStructPresentFlag)
        {
            picStruct = reader.readBits<std::uint8_t, 4>();
            auto iter = std::find_if(std::begin(context.interpreatationOfPicStruct), std::end(context.interpreatationOfPicStruct), [=](const InterpretationOfPicStruct& ips) { return ips.value == picStruct; });
            if (iter == std::end(context.interpreatationOfPicStruct))
            {
                throw std::runtime_error("failed to decoding timing info");
            }
            for (auto i = 0; i < iter->numClockTs; i++)
            {
                ClockTS cts;
                cts.clockTimestampFlag = reader.readBits<std::uint8_t, 1>();
                if (cts.clockTimestampFlag)
                {
                    cts.ctType = reader.readBits<std::uint8_t, 2>();
                    cts.nuitFieldBasedFlag = reader.readBits<std::uint8_t, 1>();
                    cts.countingType = reader.readBits<std::uint8_t, 5>();
                    cts.fullTimestampFlag = reader.readBits<std::uint8_t, 1>();
                    cts.discontinuityFlag = reader.readBits<std::uint8_t, 1>();
                    cts.cntDroppedFlag = reader.readBits<std::uint8_t, 1>();
                    cts.nFrames = reader.readBits<std::uint8_t, 8>();
                    if (cts.fullTimestampFlag)
                    {
                        cts.secondsValue = reader.readBits<std::uint8_t, 6>();
                        cts.minutesValue = reader.readBits<std::uint8_t, 6>();
                        cts.hoursValue = reader.readBits<std::uint8_t, 5>();
                    }
                    else
                    {
                        cts.secondsFlag = reader.readBits<std::uint8_t, 1>();
                        if (cts.secondsFlag)
                        {
                            cts.secondsValue = reader.readBits<std::uint8_t, 6>();
                            cts.minutesFlag = reader.readBits<std::uint8_t, 1>();
                            if (cts.minutesFlag)
                            {
                                cts.minutesValue = reader.readBits<std::uint8_t, 6>();
                                cts.hoursFlag = reader.readBits<std::uint8_t, 1>();
                                if (cts.hoursFlag)
                                {
                                    cts.hoursValue = reader.readBits<std::uint8_t, 5>();
                                }
                            }
                        }
                    }
                    if (context.currentSPS().spsData.vuiParameters.hrdParameters.timeOffsetLength > 0)
                    {
                        cts.timeOffset = reader.readBits<std::int16_t>(context.currentSPS().spsData.vuiParameters.hrdParameters.timeOffsetLength);
                    }
                }
                clockTSs.emplace_back(cts);
            }
        }
    }

};


