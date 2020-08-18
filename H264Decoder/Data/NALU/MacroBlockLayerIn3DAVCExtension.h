#pragma once
#include <IO/BitstreamReader.h>


struct MacroBlockLayerIn3DAVCExtension
{
    std::uint8_t mbType{};
    bool mbDirectTypeFlag{};
    bool mbAlcFlag{};
    std::uint8_t pcmAlignmentZeroBit{};
    std::uint8_t pcmSampleLuma[256]{};
    std::vector<std::uint8_t> pcmSampleChroma;

    SubMbPredIn3DAVCExtension subMbPredIn3DAVCExtension;
    bool transformSize8x8Flag{};
    std::uint8_t codedBlockPattern{};
    MbPredIn3DAVCExtension mbPredIn3DAVCExtension;
    std::uint8_t mbQpDelta{};

    Residual residual;
};



