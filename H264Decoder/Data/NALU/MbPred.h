#pragma once
#include <IO/BitstreamReader.h>


struct MbPred
{
    std::vector<Intra4x4Pred> intra4x4Pred;
    std::uint8_t intraChromaPredMOde = 0;
    std::vector<AeV> refIdxl0;
    std::vector<AeV> refIdxl1;
    std::vector<AeV> mvdl0;
    std::vector<AeV> mvdl1;
};


