#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/SPSData.h>
#include <Data/NALU/RbspTrailingBits.h>

struct DecodingContext;
struct NALUnit;

struct SPSRbsp
{
    SPSData spsData;

    RbspTrailingBits rbspTrailingBits;

    SPSRbsp() = default;
    explicit SPSRbsp(DecodingContext& context, BitstreamReader& reader, NALUnit&);
};



