#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/SubMbPred.h>
#include <Data/NALU/MbPred.h>
#include <Data/NALU/Residual.h>


struct MacroBlockLayer
{
    std::uint8_t mbType = 0;
    std::uint8_t pcmAligmentZeroBit = 0;
    std::vector<Byte> PcmByte;

    SubMbPred subMbPred;
    MbPred mbPred;
    std::uint8_t codedBlockPattern = 0;
    std::uint8_t mbQpDelta = 0;
    Residual residual;
};


