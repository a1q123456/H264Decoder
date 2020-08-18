#pragma once
#include <IO/BitstreamReader.h>


struct ResidualBlockCabac
{
    bool codedBlockFlag = false;
    std::vector<CodedBlock> codedBlocks;
    std::vector<Coeff> coeffs;

};


