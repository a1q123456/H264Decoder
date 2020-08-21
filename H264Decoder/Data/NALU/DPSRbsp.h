#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\DepthRange.h>
#include <Data\NALU\VspParam.h>
#include <Data/NALU/RbspTrailingBits.h>

struct DecodingContext;

struct DPSRbsp
{
    std::uint16_t dpsId = 0;
    std::uint16_t predDirection = 0;

    std::uint16_t refDpsId0 = 0;
    std::uint16_t refDpsId1 = 0;
    std::uint8_t predWeight0 = 0;

    std::uint16_t numDepthViewsMinus1 = 0;
    DepthRange depthRanges;

    bool vspParamFlag = false;
    VspParam vspParam;

    bool depthParamAdditionalExtensionFlag = false;
    std::uint16_t nonlinearDepthRepresentationNum = 0;
    std::vector<std::uint16_t> nonlinearDepthRepresentationModel;

    std::vector<BoolType> depthParamAdditionalExtensionDataFlags;

    RbspTrailingBits rbspTrailingBits;

    DPSRbsp() = default;
    explicit DPSRbsp(DecodingContext& context, BitstreamReader& reader);

};

