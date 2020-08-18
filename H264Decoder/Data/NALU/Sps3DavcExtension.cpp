#include "pch.h"
#include "Sps3DavcExtension.h"
#include <Data/DecodingContext.h>

Sps3DavcExtension::Sps3DavcExtension(DecodingContext& context, BitstreamReader& reader, int numDepthViews)
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
