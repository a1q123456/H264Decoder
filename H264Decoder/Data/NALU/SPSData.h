#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/FrameCropping.h>
#include <Data\NALU\VuiParameters.h>
#include <Data\NALU\ScalingList.h>

struct SPSData
{
    std::uint8_t chromaArrayType = 0;

    std::uint8_t profileIdc = 0;

    bool constraintSet0Flag = false;
    bool constraintSet1Flag = false;
    bool constraintSet2Flag = false;
    bool constraintSet3Flag = false;
    bool constraintSet4Flag = false;
    bool constraintSet5Flag = false;

    std::uint8_t reservedZero2Bits = 0;

    std::uint8_t levelIdc = 0;
    std::uint16_t spsId = 0;
    std::uint16_t chromaFormatIdc = 0;
    bool separateColourPlaneFlag = false;
    std::uint16_t bitDepthLumaMinus8 = 0;
    std::uint16_t bitDepthChromaMinus8 = 0;
    bool qpprimeYZeroTransformBypassFlag = false;
    bool seqScalingMatrixPresentFlag = false;
    std::vector<ScalingList> scalingList4x4;
    std::vector<ScalingList> scalingList8x8;

    std::uint16_t log2MaxFrameNumMinus4 = 0;
    std::uint16_t picOrderCntType = 0;

    std::uint16_t log2MaxPicOrderCntLsbMinus4 = 0;

    std::uint8_t deltaPicOrderAlwaysZeroFlag = 0;
    std::int16_t offsetForNonRefPic;
    std::int16_t offsetForTopToBottomField;
    std::uint16_t numRefFramesInPicOrderCntCycle = 0;
    std::vector<std::int16_t> offsetForRefFrame;

    std::uint16_t numRefFrames = 0;
    bool gapsInFrameNumValueAllowedFlag = false;
    std::uint16_t picWidthInMbsMinus1 = 0;
    std::uint16_t picHeightInMapUnitsMinus1 = 0;
    std::uint32_t picSizeInMapUnits = 0;
    bool frameMbsOnlyFlag = false;
    bool mbAdaptiveFrameFieldFlag = false;
    bool direct8x8InferenceFlag = false;
    bool frameCroppingFlag = false;
    FrameCropping frameCropping;


    bool vuiParametersPresentFlag = false;
    VuiParameters vuiParameters;

    SPSData() = default;

    explicit SPSData(BitstreamReader& rbspReader)
    {
        profileIdc = rbspReader.readBits<std::uint8_t, 8>();
        constraintSet0Flag = rbspReader.readBits<std::uint8_t, 1>();
        constraintSet1Flag = rbspReader.readBits<std::uint8_t, 1>();
        constraintSet2Flag = rbspReader.readBits<std::uint8_t, 1>();
        constraintSet3Flag = rbspReader.readBits<std::uint8_t, 1>();
        constraintSet4Flag = rbspReader.readBits<std::uint8_t, 1>();
        constraintSet5Flag = rbspReader.readBits<std::uint8_t, 1>();
        auto reserved = rbspReader.readBits<std::uint8_t, 2>();
        if (reserved != 0)
        {
            throw std::runtime_error("not supported");
        }

        levelIdc = rbspReader.readBits<std::uint8_t, 8>();
        spsId = rbspReader.readExpoGlomb();
        if (profileIdc == 100 || profileIdc == 110 ||
            profileIdc == 122 || profileIdc == 244 || profileIdc == 44 ||
            profileIdc == 83 || profileIdc == 86 || profileIdc == 118 ||
            profileIdc == 128 || profileIdc == 138 || profileIdc == 139 ||
            profileIdc == 134)
        {
            chromaFormatIdc = rbspReader.readExpoGlomb();
            if (chromaFormatIdc == 3)
            {
                separateColourPlaneFlag = rbspReader.readBits<std::uint8_t, 1>();
            }

            chromaArrayType = !separateColourPlaneFlag ? chromaFormatIdc : 0;
            bitDepthLumaMinus8 = rbspReader.readExpoGlomb();
            bitDepthChromaMinus8 = rbspReader.readExpoGlomb();
            qpprimeYZeroTransformBypassFlag = rbspReader.readBits<std::uint8_t, 1>();
            seqScalingMatrixPresentFlag = rbspReader.readBits<std::uint8_t, 1>();
            if (seqScalingMatrixPresentFlag)
            {
                for (auto i = 0; i < ((chromaFormatIdc != 3) ? 8 : 12); i++)
                {
                    auto&& list = i < 6 ? scalingList4x4.emplace_back() : scalingList8x8.emplace_back();
                    auto present = rbspReader.readBits<std::uint8_t, 1>();
                    if (present)
                    {
                        list.scalingList.resize(i < 6 ? 16 : 64);
                        readScalingList(rbspReader, list.scalingList, list.scalingList.size(), list.useDefaultFlag);
                    }
                }
            }
        }
        log2MaxFrameNumMinus4 = rbspReader.readExpoGlomb();
        picOrderCntType = rbspReader.readExpoGlomb();
        if (picOrderCntType == 0)
        {
            log2MaxPicOrderCntLsbMinus4 = rbspReader.readExpoGlomb();
        }
        else if (picOrderCntType == 1)
        {
            deltaPicOrderAlwaysZeroFlag = rbspReader.readBits<std::uint8_t, 1>();
            offsetForNonRefPic = rbspReader.readSignedExpoGlomb();
            offsetForTopToBottomField = rbspReader.readSignedExpoGlomb();
            numRefFramesInPicOrderCntCycle = rbspReader.readExpoGlomb();
            for (auto i = 0; i < numRefFramesInPicOrderCntCycle; i++)
            {
                offsetForRefFrame.push_back(rbspReader.readSignedExpoGlomb());
            }
        }
        numRefFrames = rbspReader.readExpoGlomb();
        gapsInFrameNumValueAllowedFlag = rbspReader.readBits<std::uint8_t, 1>();
        picWidthInMbsMinus1 = rbspReader.readExpoGlomb();
        picHeightInMapUnitsMinus1 = rbspReader.readExpoGlomb();
        picSizeInMapUnits = (picWidthInMbsMinus1 + 1) * (picHeightInMapUnitsMinus1 + 1);
        frameMbsOnlyFlag = rbspReader.readBits<std::uint8_t, 1>();
        if (!frameMbsOnlyFlag)
        {
            mbAdaptiveFrameFieldFlag = rbspReader.readBits<std::uint8_t, 1>();
        }
        direct8x8InferenceFlag = rbspReader.readBits<std::uint8_t, 1>();
        frameCroppingFlag = rbspReader.readBits<std::uint8_t, 1>();
        if (frameCroppingFlag)
        {
            frameCropping = FrameCropping{ rbspReader };
        }
        vuiParametersPresentFlag = rbspReader.readBits<std::uint8_t, 1>();
        if (vuiParametersPresentFlag)
        {
            vuiParameters = VuiParameters(rbspReader);
        }


    }
};

