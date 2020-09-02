#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\RbspTrailingBits.h>

struct DecodingContext;

struct RbspSliceTrailingBits
{
    RbspTrailingBits rbspTrailingBits;
    std::uint16_t cabacZeroWord = 0;

    RbspSliceTrailingBits() = default;
    explicit RbspSliceTrailingBits(DecodingContext& context, BitstreamReader& reader);

};


