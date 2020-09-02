#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\RefPicListModification.h>
#include <Data\NALU\DecRefBasePicMarking.h>
#include <Data/NALU/PredWeightTable.h>
#include <Data/NALU/DecRefPicMarking.h>

struct DecodingContext;
struct NALUnit;

struct SliceHeaderInScalableExtension
{
    std::uint16_t firstMbInSlice = 0;
    std::uint16_t sliceType = 0;
    std::uint16_t ppsId = 0;

    std::uint8_t colourPlaneId = 0;
    std::uint32_t frameNum = 0;

    bool fieldPicFlag = false;
    bool bottomFieldFlag = false;

    std::uint16_t idrPicId = 0;
    std::uint32_t picOrderCntLsb = 0;

    std::int16_t deltaPicOrderCntBottom;
    std::int16_t deltaPicOrderCnt[2];

    std::uint16_t redundantPicCnt = 0;
    bool directSpatialMvPredFlag = false;
    bool numRefIdxActiveOverrideFlag = false;
    std::uint16_t numRefIdxL0ActiveMinus1 = 0;
    std::uint16_t numRefIdxL1ActiveMinus1 = 0;

    RefPicListModification refPicListModification;

    bool basePredWeightTableFlag = false;
    PredWeightTable predWeightTable;

    DecRefPicMarking decRefPicMarking;
    bool storeRefBasePicFlag = false;
    DecRefBasePicMarking decRefBasePicMarking;

    std::uint16_t cabacInitIdc = 0;
    std::int16_t sliceQpDelta;

    std::uint16_t disableDeblockingFilterIdc = 0;
    std::int16_t sliceAlphaC0OffsetDiv2;
    std::int16_t sliceBetaOffsetDiv2;

    std::uint8_t sliceGroupChangeCycle = 0;
    std::uint16_t refLayerDqId = 0;
    std::uint16_t disableInterLayerDeblockingFilterIdc = 0;
    std::int16_t interLayerSliceAlphaC0OffsetDiv2;
    std::int16_t interLayerSliceBetaOffsetDiv2;

    bool constrainedIntraResamplingFlag = false;
    bool refLayerChromaPhaseXPlus1Flag = false;
    std::uint8_t refLayerChromaPhaseYPlus1 = 0;

    std::int16_t scaledRefLayerLeftOffset;
    std::int16_t scaledRefLayerTopOffset;
    std::int16_t scaledRefLayerRightOffset;
    std::int16_t scaledRefLayerBottomOffset;

    bool sliceSkipFlag = false;
    std::uint16_t numMbsInSliceMinus1 = 0;

    bool adaptiveBaseModeFlag = false;
    bool defaultBaseModeFlag = false;
    bool adaptiveMotionPredictionFlag = false;
    bool defaultMotionPredictionFlag = false;
    bool adaptiveResidualPredictionFlag = false;
    bool defaultResidualPredictionFlag = false;
    bool tcoeffLevelPredictionFlag = false;

    std::uint8_t scanIdxStart = 0;
    std::int8_t scanIdxEnd;

    SliceHeaderInScalableExtension() = default;
    explicit SliceHeaderInScalableExtension(DecodingContext& context, BitstreamReader& reader, NALUnit& nal);
};


