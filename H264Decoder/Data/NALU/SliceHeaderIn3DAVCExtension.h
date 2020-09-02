#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\RefPicListMvcModification.h>
#include <Data\NALU\RefPicListModification.h>
#include <Data\NALU\PredWeightTable.h>


struct SliceHeaderIn3DAVCExtension
{
    std::uint8_t firstMbInSlice = 0;
    std::uint8_t sliceType = 0;
    std::uint8_t ppsId = 0;
    std::uint8_t preSliceHeaderSrc = 0;
    std::uint8_t preRefListsSrc = 0;
    bool numRefIdxActiveOverrideFlag = false;
    std::uint8_t numRefIdxL0ActiveMinus1 = 0;
    std::uint8_t numRefIdxL1ActiveMinus1 = 0;

    RefPicListMvcModification refPicListMvcModification;
    std::uint8_t prePredWeightTableSrc = 0;
    PredWeightTable predWeightTable;
    std::uint8_t preDecRefPicMarkingSrc = 0;
    DecRefPicMarking decRefPicMarking;
    std::int8_t sliceQpDelta;

    std::int8_t colourPlaneId;
    std::uint8_t frameNum = 0;
    bool fieldPicFlag = false;
    bool bottomFieldFlag = false;

    std::uint8_t idrPicId = 0;
    std::uint8_t picOrderCntLsb = 0;
    std::int8_t deltaPicOrderCntBottom;
    std::int8_t deltaPicOrderCnt[2];

    std::uint8_t redundantPicCnt = 0;

    bool directSpatialMvPredFlag = false;
    RefPicListModification refPicListModification;
    std::uint8_t cabacInitIdc = 0;
    bool spForSwitchFlag = false;
    std::int8_t sliceQsDelta;

    std::uint8_t disableDeblockingFilterIdc = 0;
    std::int8_t sliceAlphaC0OffsetDiv2;
    std::int8_t sliceBetaOffsetDiv2;

    std::uint8_t sliceGroupChangeCycle = 0;
    bool depthWeightedPredFlag = false;
    bool dmvpFlag = false;
    bool sliceVspFlag = false;

    std::uint8_t dpsId = 0;

};


