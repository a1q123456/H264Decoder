#pragma once
#include <IO/BitstreamReader.h>


struct SubMbPred
{
    std::array<AeV, 4> subMbType;
    std::array<AeV, 4> refIdxl0;
    std::array<AeV, 4> refIdxl1;
    std::array<std::vector<std::array<AeV, 2>>, 4> mvdl0;
    std::array<std::vector<std::array<AeV, 2>>, 4> mvdl1;
};



