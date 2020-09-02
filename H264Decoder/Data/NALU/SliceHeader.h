#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\RefPicListReordering.h>
#include <Data\NALU\PredWeightTable.h>
#include <Data\NALU\DecRefPicMarking.h>


struct SliceHeader
{
    std::uint16_t firstMbInSlice = 0;
    std::uint8_t sliceType = 0;
    std::uint8_t picParameterSetID = 0;
    std::uint8_t frameNum = 0;
    bool fieldPicFlag = false;
    bool bottomFieldFlag = false;

    std::uint8_t idrPicID = 0;
    std::uint8_t picOrderCntLsb = 0;
    std::int8_t deltaPicOrderCntBottom;

    std::int8_t deltaPicOrderCnt[2];
    std::uint8_t redundantPicCnt = 0;
    bool directSpatialMVPredFlag = false;
    bool numRefIdxActiveOverrideFlag = false;
    std::uint8_t numRefIdxL0ActiveMinus1 = 0;
    std::uint8_t numRefIdxL1ActiveMinus1 = 0;

    RefPicListReordering refPicListRecording;
    PredWeightTable predWeightTable;
    DecRefPicMarking decRefPicMarking;
    std::uint8_t cabacInitIdc = 0;
    std::int8_t sliceQPDelta;
    bool spForSwitchFlag = false;
    std::int8_t sliceQSDelta;
    std::uint8_t disableDeblockingFilterIdc = 0;

    std::int8_t sliceAlphaC0OffsetDiv2;
    std::int8_t sliceBetaOffsetDiv2;

    std::uint8_t sliceGroupChangeCycle = 0;

};


