#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/SubMbPredInScalableExtension.h>
#include <Data/NALU/MbPredInScalableExtension.h>
#include <Data/NALU/Residual.h>


struct MacroBlockLayerInScalableExtension
{
    bool baseModeFlag = false;
    std::uint8_t mbType = 0;
    std::uint8_t pcmAlignmentZeroBit = 0;

    std::uint8_t pcmSampleLuma[256]{};
    std::vector<std::uint8_t> pcmSampleChroma;

    SubMbPredInScalableExtension subMbPredInScalableExtension;
    bool transformSize8x8Flag = false;
    MbPredInScalableExtension mbPredInScalableExtension;

    bool residualPredictionFLag = false;
    std::uint8_t codedBlockPattern = 0;
    std::uint8_t mbQpDelta = 0;

    Residual residual;

    MacroBlockLayerInScalableExtension() = default;
    explicit MacroBlockLayerInScalableExtension(BitstreamReader& reader);
};


