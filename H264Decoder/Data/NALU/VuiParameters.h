#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/VuiTimingInfo.h>
#include <Data/NALU/HrdParameters.h>
#include <Data\CommonValues.h>


struct VuiParameters
{
    bool aspectRationInfoPresentFlag = false;
    std::uint8_t aspectRatioIdc = 0;
    std::uint16_t sarWidth = 0;
    std::uint16_t sarHeight = 0;

    bool overscanInfoPresentFlag = false;
    bool overscanAppropriateFlag = false;
    bool videoSignalTypePresentFlag = false;

    std::uint8_t videoFormat = 0;
    bool videoFullRangeFlag = false;
    bool colourDescriptionPresentFlag = false;

    std::uint8_t colourPrimaries = 0;
    std::uint8_t transferCharacteristics = 0;
    std::uint8_t matrixCoefficients = 0;

    bool chromaLocInfoPresentFlag = false;
    std::uint8_t chromaSampleLocTypeTopField = 0;
    std::uint8_t chromaSampleLocTypeBottomField = 0;

    bool timingInfoPresentFlag = false;
    VuiTimingInfo timingInfo;

    bool nalHrdParametersPresentFlag = false;
    bool vclHrdParametersPresentFlag = false;

    HrdParameters hrdParameters;

    bool lowDelayHrdFlag = false;
    bool picStructPresentFlag = false;
    bool bitstreamRestrictionFlag = false;

    bool motionVectorsOverPicBoundariesFlag = false;
    std::uint8_t maxBytesPerPicDenom = 0;
    std::uint8_t maxBitsPerMbDenom = 0;
    std::uint8_t log2MaxMvLengthHorizontal = 0;
    std::uint8_t log2MaxMvLengthVertical = 0;
    std::uint8_t numRecorderFrames = 0;
    std::uint8_t maxDecFrameBuffering = 0;

    VuiParameters() = default;
    explicit VuiParameters(BitstreamReader& rbspReader)
    {
        aspectRationInfoPresentFlag = rbspReader.readBits<std::uint8_t, 1>();
        if (aspectRationInfoPresentFlag)
        {
            aspectRatioIdc = rbspReader.readBits<std::uint8_t, 8>();
            if (aspectRatioIdc == Extended_SAR)
            {
                sarWidth = rbspReader.readBits<std::uint16_t, 16>();
                sarHeight = rbspReader.readBits<std::uint16_t, 16>();
            }
        }
        overscanInfoPresentFlag = rbspReader.readBits<std::uint8_t, 1>();
        if (overscanInfoPresentFlag)
        {
            overscanAppropriateFlag = rbspReader.readBits<std::uint8_t, 1>();
        }
        videoSignalTypePresentFlag = rbspReader.readBits<std::uint8_t, 1>();
        if (videoSignalTypePresentFlag)
        {
            videoFormat = rbspReader.readBits<std::uint8_t, 3>();
            videoFullRangeFlag = rbspReader.readBits<std::uint8_t, 1>();
            colourDescriptionPresentFlag = rbspReader.readBits<std::uint8_t, 1>();
            if (colourDescriptionPresentFlag)
            {
                colourPrimaries = rbspReader.readBits<std::uint8_t, 8>();
                transferCharacteristics = rbspReader.readBits<std::uint8_t, 8>();
                matrixCoefficients = rbspReader.readBits<std::uint8_t, 8>();
            }
        }
        chromaLocInfoPresentFlag = rbspReader.readBits<std::uint8_t, 1>();
        if (chromaLocInfoPresentFlag)
        {
            chromaSampleLocTypeTopField = rbspReader.readExpoGlomb();
            chromaSampleLocTypeBottomField = rbspReader.readExpoGlomb();
        }
        timingInfoPresentFlag = rbspReader.readBits<std::uint8_t, 1>();
        if (timingInfoPresentFlag)
        {
            timingInfo = VuiTimingInfo{ rbspReader };
        }
        nalHrdParametersPresentFlag = rbspReader.readBits<std::uint8_t, 1>();
        if (nalHrdParametersPresentFlag)
        {
            hrdParameters = HrdParameters(rbspReader);
        }
        vclHrdParametersPresentFlag = rbspReader.readBits<std::uint8_t, 1>();
        if (vclHrdParametersPresentFlag)
        {
            hrdParameters = HrdParameters(rbspReader);
        }
        if (nalHrdParametersPresentFlag || vclHrdParametersPresentFlag)
        {
            lowDelayHrdFlag = rbspReader.readBits<std::uint8_t, 1>();
        }
        picStructPresentFlag = rbspReader.readBits<std::uint8_t, 1>();
        bitstreamRestrictionFlag = rbspReader.readBits<std::uint8_t, 1>();
        if (bitstreamRestrictionFlag)
        {
            motionVectorsOverPicBoundariesFlag = rbspReader.readBits<std::uint8_t, 1>();
            maxBytesPerPicDenom = rbspReader.readExpoGlomb();
            maxBitsPerMbDenom = rbspReader.readExpoGlomb();
            log2MaxMvLengthHorizontal = rbspReader.readExpoGlomb();
            log2MaxMvLengthVertical = rbspReader.readExpoGlomb();
            numRecorderFrames = rbspReader.readExpoGlomb();
            maxDecFrameBuffering = rbspReader.readExpoGlomb();
        }
    }

};


