#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\GridPosView.h>
#include <Data/NALU/DepthRange.h>
#include <Data/NALU/VspParam.h>
#include <Data\NALU\FrameCropping.h>

struct DecodingContext;

struct Sps3DavcExtension
{
    std::uint16_t threeDVAcquisitionIdc = 0;
    std::vector<std::uint16_t> viewId3Dv;

    DepthRange depthRanges;
    VspParam vspParam;

    bool reducedResolutionFlag = false;
    std::uint16_t depthPicWidthInMbsMinus1 = 0;
    std::uint16_t depthPicHeightInMapUnitsMinus1 = 0;
    std::uint16_t depthHorMultMinus1 = 0;
    std::uint16_t depthVerMultMinus1 = 0;
    std::uint16_t depthHorRsh = 0;
    std::uint16_t depthVerRsh = 0;

    bool depthFrameCroppingFlag = false;
    FrameCropping depthFrameCropping;

    std::uint16_t gridPosNumViews = 0;
    std::vector<GridPosView> gridPosViews;

    bool sliceHeaderPredictionFlag = false;
    bool seqViewSynthesisFlag = false;

    bool alcSpsEnableFlag = false;
    bool enableRleSkipFlag = false;

    Sps3DavcExtension() = default;
    explicit Sps3DavcExtension(DecodingContext& context, BitstreamReader& reader, int numDepthViews);
};


