#pragma once
#include <IO/BitstreamReader.h>


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
    explicit Sps3DavcExtension(DecodingContext& context, BitstreamReader& reader, int numDepthViews)
    {
        if (numDepthViews > 0)
        {
            threeDVAcquisitionIdc = reader.readExpoGlomb();
            for (auto i = 0; i < numDepthViews; i++)
            {
                viewId3Dv.emplace_back(reader.readExpoGlomb());
            }
            if (threeDVAcquisitionIdc)
            {
                depthRanges = DepthRange{ context, reader, numDepthViews, 2, 0 };
                vspParam = VspParam{ reader, numDepthViews, 2, 0 };
            }
            reducedResolutionFlag = reader.readBits<std::uint8_t, 1>();
            if (reducedResolutionFlag)
            {
                depthPicWidthInMbsMinus1 = reader.readExpoGlomb();
                depthPicHeightInMapUnitsMinus1 = reader.readExpoGlomb();
                depthHorMultMinus1 = reader.readExpoGlomb();
                depthVerMultMinus1 = reader.readExpoGlomb();
                depthHorRsh = reader.readExpoGlomb();
                depthVerRsh = reader.readExpoGlomb();
            }
            gridPosNumViews = reader.readExpoGlomb();
            for (auto i = 0; i < gridPosNumViews; i++)
            {
                gridPosViews.emplace_back(reader);
            }
            sliceHeaderPredictionFlag = reader.readBits<std::uint8_t, 1>();
            seqViewSynthesisFlag = reader.readBits<std::uint8_t, 1>();
        }
        alcSpsEnableFlag = reader.readBits<std::uint8_t, 1>();
        enableRleSkipFlag = reader.readBits<std::uint8_t, 1>();
    }
};


