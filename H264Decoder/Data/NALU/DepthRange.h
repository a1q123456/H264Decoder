#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\ThreeDVAcquisitionElement.h>

struct DecodingContext;

struct DepthRange
{
    bool zNearFlag = false;
    bool zFarFlag = false;

    ThreeDVAcquisitionElement threeDVAcquisitionElement;

    DepthRange() = default;
    explicit DepthRange(DecodingContext& context, BitstreamReader& reader, int numViews, int predDirection, int index);
};

