#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/RbspTrailingBits.h>
#include <Data/NALU/ScalingList.h>

struct DecodingContext;
struct NALUnit;

struct PPSRbsp
{
    std::uint16_t ppsId = 0;
    std::uint16_t spsId = 0;
    bool entropyCodingModeFlag = false;
    bool bottomFieldPicOrderInFramePresentFlag = false;

    std::uint16_t numSliceGroupsMinus1 = 0;
    std::uint16_t sliceGroupMapType = 0;
    std::vector<std::uint16_t> runLengthMinus1;
    std::vector<std::uint16_t> topLeft;
    std::vector<std::uint16_t> bottomRight;
    bool sliceGroupChangeDirectionFlag = false;
    std::uint16_t picSizeInMapUnitsMinus1 = 0;
    std::uint16_t sliceGroupChangeRateMinus1 = 0;

    std::vector<std::uint16_t> sliceGroupId;

    std::uint16_t numRefIdxl0DefaultActiveMinus1 = 0;
    std::uint16_t numRefIdxl1DefaultActiveMinus1 = 0;

    bool weightedPredFlag = false;
    std::uint8_t weightedBipredIdc = 0;
    std::int16_t picInitQPMinus26;
    std::int16_t picInitQSMinus26;
    std::int16_t chromaQPIndexOffset;

    bool deblockingFilterControlPresentFlag = false;
    bool constraintedIntraPredFlag = false;
    bool redundantPicCntPresentFlag = false;

    bool transform8x8ModeFlag = false;
    bool picScalingMatrixPresentFlag = false;

    std::vector<ScalingList> scalingList4x4;
    std::vector<ScalingList> scalingList8x8;

    std::int16_t secondChromaQPIndexOffset;


    RbspTrailingBits rbspTrailingBits;

    PPSRbsp() = default;
    explicit PPSRbsp(DecodingContext& context, BitstreamReader& reader, NALUnit&);
};


