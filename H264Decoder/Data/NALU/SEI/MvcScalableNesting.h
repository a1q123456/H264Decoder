#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALUnit.h>
#include <Data/NALU/SEI/SEIMessage.h>

struct DecodingContext;

struct MvcScalableNesting
{
    bool operationPointFlag = false;
    bool allViewComponentsInAuFlag = false;
    std::uint32_t numViewComponentsMinus1;

    std::vector<std::uint16_t> seiViewId;

    std::uint32_t numViewComponentsOpMinus1 = 0;
    std::vector<std::uint16_t> seiOpViewId;
    std::uint8_t seiOpTemporalId = 0;

    std::uint8_t seiNestingZeroBit = 0;
    SEIMessage seiMessage;

    MvcScalableNesting() = default;
    explicit MvcScalableNesting(BitstreamReader& reader, DecodingContext& context, NALUnit& nalu);
};



