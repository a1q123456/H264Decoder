#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\GridPosView.h>

struct DecodingContext;

struct Sps3DavcExtension
{
    std::uint8_t threeDVAcquisitionIdc = 0;
    std::vector<std::uint8_t> viewId3Dv;

    DepthRange depthRanges;
    VspParam vspParam;

    bool reducedResolutionFlag = false;
    std::uint8_t depthPicWidthInMbsMinus1 = 0;
    std::uint8_t depthPicHeightInMapUnitsMinus1 = 0;
    std::uint8_t depthHorMultMinus1 = 0;
    std::uint8_t depthVerMultMinus1 = 0;
    std::uint8_t depthHorRsh = 0;
    std::uint8_t depthVerRsh = 0;

    bool depthFrameCroppingFlag = false;
    FrameCropping depthFrameCropping;

    std::uint8_t gridPosNumViews = 0;
    std::vector<GridPosView> gridPosViews;

    bool sliceHeaderPredictionFlag = false;
    bool seqViewSynthesisFlag = false;

    bool alcSpsEnableFlag = false;
    bool enableRleSkipFlag = false;

    Sps3DavcExtension() = default;
    explicit Sps3DavcExtension(DecodingContext& context, BitstreamReader& reader, int numDepthViews);
};


