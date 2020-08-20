#pragma once
#include <IO/BitstreamReader.h>


struct OperationPoint
{
    bool isMvcdFlag = false;
    std::uint32_t operationPointId = 0;
    std::uint8_t priorityId = 0;
    std::uint8_t   temporalId = 0;
    std::uint32_t numTargetOutputViewsMinus1 = 0;
    std::vector<TargetOutputView> targetOutputViews;

    bool profileLevelInfoPresentFlag = false;
    bool bitrateInfoPresentFlag = false;
    bool frmRateInfoPresentFlag = false;
    bool viewDependencyInfoPresentFlag = false;
    bool parameterSetsInfoPresentFlag = false;
    bool bitstreamRestrictionInfoPresentFlag = false;
    std::uint32_t opProfileLevelIdc = 0;
    std::uint16_t avgBitrate = 0;
    std::uint16_t maxBitrate = 0;
    std::uint16_t maxBitrateCalcWindow = 0;

    std::uint8_t constantFrmRateIdc = 0;
    std::uint16_t avgFrmRate;

    std::uint32_t numDirectlyDependentViews = 0;
    std::vector<DirectlyDependentView> directlyDependentViews;

    std::uint32_t viewDependencyInfoSrcOpId = 0;

    std::uint32_t numSeqParameterSets = 0;
    std::vector<std::uint32_t> seqParameterSetIdDelta;

    std::uint32_t numSubsetSeqParameterSets = 0;
    std::vector<std::uint32_t> subsetSeqParameterSetIdDelta;

    std::uint32_t numPicParameterSetMinus1 = 0;
    std::vector<std::uint32_t> picParameterSetIdDelta;

    std::uint32_t parameterSetsInfoSrcOpId = 0;
    bool motionVectorsOverPicBoundariesFlag = false;
    std::uint32_t maxBytesPerPicDenom = 0;
    std::uint32_t maxBitsPerMbDenom = 0;
    std::uint32_t log2MaxMvLengthHorizontal = 0;
    std::uint32_t log2MaxMvLengthVertical = 0;
    std::uint32_t maxNumReorderFrames = 0;
    std::uint32_t maxDecFrameBuffering = 0;

    OperationPoint() = default;
    explicit OperationPoint(BitstreamReader& reader, bool isMvcd)
    {
        isMvcdFlag = isMvcd;
        operationPointId = reader.readExpoGlomb();
        priorityId = reader.readBits<std::uint8_t, 5>();
        temporalId = reader.readBits<std::uint8_t, 3>();
        numTargetOutputViewsMinus1 = reader.readExpoGlomb();
        for (auto j = 0; j <= numTargetOutputViewsMinus1; j++)
        {
            targetOutputViews.emplace_back(reader, isMvcd);
        }
        profileLevelInfoPresentFlag = reader.readBits<bool, 1>();
        bitrateInfoPresentFlag = reader.readBits<bool, 1>();
        frmRateInfoPresentFlag = reader.readBits<bool, 1>();
        if (!numTargetOutputViewsMinus1)
        {
            viewDependencyInfoPresentFlag = reader.readBits<bool, 1>();
        }
        parameterSetsInfoPresentFlag = reader.readBits<bool, 1>();
        bitstreamRestrictionInfoPresentFlag = reader.readBits<bool, 1>();
        if (profileLevelInfoPresentFlag)
        {
            opProfileLevelIdc = reader.readBits<std::uint32_t, 24>();
        }
        if (bitrateInfoPresentFlag)
        {
            avgBitrate = reader.readBits<std::uint16_t, 16>();
            maxBitrate = reader.readBits<std::uint16_t, 16>();
            maxBitrateCalcWindow = reader.readBits<std::uint16_t, 16>();
        }
        if (frmRateInfoPresentFlag)
        {
            constantFrmRateIdc = reader.readBits<std::uint8_t, 2>();
            avgFrmRate = reader.readBits<std::uint16_t, 16>();
        }
        if (viewDependencyInfoPresentFlag)
        {
            numDirectlyDependentViews = reader.readExpoGlomb();
            for (auto j = 0; j < numDirectlyDependentViews; j++)
            {
                directlyDependentViews.emplace_back(reader, isMvcd);
            }
        }
        else
        {
            viewDependencyInfoSrcOpId = reader.readExpoGlomb();
        }
        if (parameterSetsInfoPresentFlag)
        {
            numSeqParameterSets = reader.readExpoGlomb();
            for (auto j = 0; j < numSeqParameterSets; j++)
            {
                seqParameterSetIdDelta.emplace_back(reader.readExpoGlomb());
            }
            numSubsetSeqParameterSets = reader.readExpoGlomb();
            for (auto j = 0; j < numSubsetSeqParameterSets; j++)
            {
                subsetSeqParameterSetIdDelta.emplace_back(reader.readExpoGlomb());
            }
            numPicParameterSetMinus1 = reader.readExpoGlomb();
            for (auto j = 0; j <= numPicParameterSetMinus1; j++)
            {
                picParameterSetIdDelta.emplace_back(reader.readExpoGlomb());
            }
        }
        else
        {
            parameterSetsInfoSrcOpId = reader.readExpoGlomb();
        }
        if (bitstreamRestrictionInfoPresentFlag)
        {
            motionVectorsOverPicBoundariesFlag = reader.readBits<bool, 1>();
            maxBytesPerPicDenom = reader.readExpoGlomb();
            maxBitsPerMbDenom = reader.readExpoGlomb();
            log2MaxMvLengthHorizontal = reader.readExpoGlomb();
            log2MaxMvLengthVertical = reader.readExpoGlomb();
            maxNumReorderFrames = reader.readExpoGlomb();
            maxDecFrameBuffering = reader.readExpoGlomb();
        }
    }
};


