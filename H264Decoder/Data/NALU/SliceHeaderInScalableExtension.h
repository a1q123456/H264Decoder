#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\RefPicListModification.h>
#include <Data\NALU\DecRefBasePicMarking.h>

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

    std::int8_t deltaPicOrderCntBottom;
    std::int8_t deltaPicOrderCnt[2];

    std::uint8_t redundantPicCnt = 0;
    bool directSpatialMvPredFlag = false;
    bool numRefIdxActiveOverrideFlag = false;
    std::uint8_t numRefIdxl0ActiveMinus1 = 0;
    std::uint8_t numRefIdxl1ActiveMinus1 = 0;

    RefPicListModification refPicListModification;

    bool basePredWeightTableFlag = false;
    PredWeightTable predWeightTable;

    DecRefPicMarking decRefPicMarking;
    bool storeRefBasePicFlag = false;
    DecRefBasePicMarking decRefBasePicMarking;

    std::uint8_t cabacInitIdc = 0;
    std::int8_t sliceQpDelta;

    std::uint8_t disableDeblockingFilterIdc = 0;
    std::int8_t sliceAlphaC0OffsetDiv2;
    std::int8_t sliceBetaOffsetDiv2;

    std::uint8_t sliceGroupChangeCycle = 0;
    std::uint8_t refLayerDqId = 0;
    std::uint8_t disableInterLayerDeblockingFilterIdc = 0;
    std::int8_t interLayerSliceAlphaC0OffsetDiv2;
    std::int8_t interLayerSliceBetaOffsetDiv2;

    bool constrainedIntraResamplingFlag = false;
    bool refLayerChromaPhaseXPlus1Flag = false;
    std::uint8_t refLayerChromaPhaseYPlus1 = 0;

    std::int8_t scaledRefLayerLeftOffset;
    std::int8_t scaledRefLayerTopOffset;
    std::int8_t scaledRefLayerRightOffset;
    std::int8_t scaledRefLayerBottomOffset;

    bool sliceSkipFlag = false;
    std::uint8_t numMbsInSliceMinus1 = 0;

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


