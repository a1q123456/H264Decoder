#include "pch.h"
#include "SliceHeaderInScalableExtension.h"
#include <Data/DecodingContext.h>
#include <Data/NALUnit.h>

SliceHeaderInScalableExtension::SliceHeaderInScalableExtension(DecodingContext& context, BitstreamReader& reader, NALUnit& nal)
{
    firstMbInSlice = reader.readExpoGlomb();
    sliceType = reader.readExpoGlomb();
    ppsId = reader.readExpoGlomb();

    if (context.currentSPS().separateColourPlaneFlag)
    {
        colourPlaneId = reader.readBits<std::uint8_t, 2>();
    }
    frameNum = reader.readBits<std::uint32_t>(context.currentSPS().log2MaxFrameNumMinus4 + 4);
    if (!context.currentSPS().frameMbsOnlyFlag)
    {
        fieldPicFlag = reader.readBits<bool, 1>();
        if (fieldPicFlag)
        {
            bottomFieldFlag = reader.readBits<bool, 1>();
        }
    }

    if (nal.nalUnitHeaderSvcExtension.idrFlag)
    {
        idrPicId = reader.readExpoGlomb();
    }
    if (context.currentSPS().picOrderCntType == 0)
    {
        picOrderCntLsb = reader.readBits<std::uint32_t>(context.currentSPS().log2MaxPicOrderCntLsbMinus4 + 4);
        if (context.currentPPS().bottomFieldPicOrderInFramePresentFlag && fieldPicFlag)
        {
            deltaPicOrderCntBottom = reader.readSignedExpoGlomb();
        }
    }
    if (context.currentSPS().picOrderCntType == 1 && !context.currentSPS().deltaPicOrderAlwaysZeroFlag)
    {
        deltaPicOrderCnt[0] = reader.readSignedExpoGlomb();
        if (context.currentPPS().bottomFieldPicOrderInFramePresentFlag && fieldPicFlag)
        {
            deltaPicOrderCnt[1] = reader.readSignedExpoGlomb();
        }
    }
    if (context.currentPPS().redundantPicCntPresentFlag)
    {
        redundantPicCnt = reader.readExpoGlomb();
    }
    if (nal.nalUnitHeaderSvcExtension.qualityId == 0)
    {
        if (SliceType(sliceType % 5) == SliceType::EB)
        {
            directSpatialMvPredFlag = reader.readBits<bool, 1>();
        }
        if (SliceType(sliceType % 5) == SliceType::EP || SliceType(sliceType % 5) == SliceType::EB)
        {
            numRefIdxActiveOverrideFlag = reader.readBits<bool, 1>();
            if (numRefIdxActiveOverrideFlag)
            {
                numRefIdxL0ActiveMinus1 = reader.readExpoGlomb();
                if (SliceType(sliceType % 5) == SliceType::EB)
                {
                    numRefIdxL1ActiveMinus1 = reader.readExpoGlomb();
                }
            }
        }
        refPicListModification = RefPicListModification{ context, reader };
        if ((context.currentPPS().weightedPredFlag && SliceType(sliceType % 5) == SliceType::EP) ||
            (context.currentPPS().weightedBipredIdc == 1 && SliceType(sliceType % 5) == SliceType::EB))
        {
            if (!nal.nalUnitHeaderSvcExtension.noInterLayerPredFlag)
            {
                basePredWeightTableFlag = reader.readBits<bool, 1>();
            }
            if (nal.nalUnitHeaderSvcExtension.noInterLayerPredFlag || basePredWeightTableFlag)
            {
                predWeightTable = PredWeightTable{ context, reader };
            }
        }

        if (nal.nalRefIdc == 0)
        {
            decRefPicMarking = DecRefPicMarking{ nal.nalUnitType, reader };
        }
        if (!context.currentSubsetSPS().spsSvcExtension.sliceHeaderRestrictionFlag)
        {
            storeRefBasePicFlag = reader.readBits<bool, 1>();
            if ((nal.nalUnitHeaderSvcExtension.useRefBasePicFlag || storeRefBasePicFlag) &&
                (!nal.nalUnitHeaderSvcExtension.idrFlag))
            {
                decRefBasePicMarking = DecRefBasePicMarking{ reader };
            }
        }
    }
    if (context.currentPPS().entropyCodingModeFlag && SliceType(sliceType % 5) != SliceType::EI)
    {
        cabacInitIdc = reader.readExpoGlomb();
    }
    sliceQpDelta = reader.readSignedExpoGlomb();
    if (context.currentPPS().deblockingFilterControlPresentFlag)
    {
        disableDeblockingFilterIdc = reader.readExpoGlomb();
        if (disableDeblockingFilterIdc != 1)
        {
            sliceAlphaC0OffsetDiv2 = reader.readSignedExpoGlomb();
            sliceBetaOffsetDiv2 = reader.readSignedExpoGlomb();
        }
    }
    if (context.currentPPS().numSliceGroupsMinus1 > 0 &&
        context.currentPPS().sliceGroupMapType >= 3 && context.currentPPS().sliceGroupMapType <= 5)
    {
        sliceGroupChangeCycle = reader.readBits<std::uint32_t>(
            static_cast<int>(std::ceil(std::log2(context.currentSPS().picSizeInMapUnits / (context.currentPPS().sliceGroupChangeRateMinus1 + 1) + 1)))
            );
    }
    if (!nal.nalUnitHeaderSvcExtension.noInterLayerPredFlag && nal.nalUnitHeaderSvcExtension.qualityId == 0)
    {
        refLayerDqId = reader.readExpoGlomb();
        if (context.currentSubsetSPS().spsSvcExtension.interLayerDeblockingFilterControlPresentFlag)
        {
            disableInterLayerDeblockingFilterIdc = reader.readExpoGlomb();
            if (disableInterLayerDeblockingFilterIdc != 1)
            {
                interLayerSliceAlphaC0OffsetDiv2 = reader.readSignedExpoGlomb();
                interLayerSliceBetaOffsetDiv2 = reader.readSignedExpoGlomb();
            }
        }
        constrainedIntraResamplingFlag = reader.readBits<bool, 1>();
        if (context.currentSubsetSPS().spsSvcExtension.extendedSpatialScalabilityIdc == 2)
        {
            if (context.currentSPS().chromaArrayType > 0)
            {
                refLayerChromaPhaseXPlus1Flag = reader.readBits<bool, 1>();
                refLayerChromaPhaseYPlus1 = reader.readBits<std::uint8_t, 2>();
            }
            scaledRefLayerLeftOffset = reader.readSignedExpoGlomb();
            scaledRefLayerTopOffset = reader.readSignedExpoGlomb();
            scaledRefLayerRightOffset = reader.readSignedExpoGlomb();
            scaledRefLayerBottomOffset = reader.readSignedExpoGlomb();
        }
    }
    if (nal.nalUnitHeaderSvcExtension.noInterLayerPredFlag)
    {
        sliceSkipFlag = reader.readBits<bool, 1>();
        if (sliceSkipFlag)
        {
            numMbsInSliceMinus1 = reader.readExpoGlomb();
        }
        else
        {
            adaptiveBaseModeFlag = reader.readBits<bool, 1>();
            if (!adaptiveBaseModeFlag)
            {
                defaultBaseModeFlag = reader.readBits<bool, 1>();
            }
            if (!defaultBaseModeFlag)
            {
                adaptiveMotionPredictionFlag = reader.readBits<bool, 1>();
                if (!adaptiveMotionPredictionFlag)
                {
                    defaultMotionPredictionFlag = reader.readBits<bool, 1>();
                }
            }
            adaptiveResidualPredictionFlag = reader.readBits<bool, 1>();
            if (!adaptiveResidualPredictionFlag)
            {
                defaultResidualPredictionFlag = reader.readBits<bool, 1>();
            }
            if (context.currentSubsetSPS().spsSvcExtension.adaptiveTcoeffLevelPredictionFlag)
            {
                tcoeffLevelPredictionFlag = reader.readBits<bool, 1>();
            }
        }
        if (context.currentSubsetSPS().spsSvcExtension.sliceHeaderRestrictionFlag && sliceSkipFlag)
        {
            scanIdxStart = reader.readBits<std::uint8_t, 4>();
            scanIdxEnd = reader.readBits<std::uint8_t, 4>();
        }
    }
}
