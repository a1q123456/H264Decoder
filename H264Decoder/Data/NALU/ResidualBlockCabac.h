#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/CodedBlock.h>
#include <Data/NALU/Coeff.h>


struct ResidualBlockCabac
{
    bool codedBlockFlag = false;
    std::vector<CodedBlock> codedBlocks;
    std::vector<Coeff> coeffs;

};


