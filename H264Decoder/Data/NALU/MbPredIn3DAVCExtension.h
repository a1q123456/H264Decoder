#pragma once
#include <IO/BitstreamReader.h>


struct MbPredIn3DAVCExtension
{
    struct Data
    {
        std::uint8_t refIdxl0 = 0;
        bool bvspFlagl0 = false;

        std::uint8_t refIdxl1 = 0;
        bool bvspFlagl1 = false;

        std::uint8_t mvdl0[2]{};
        std::uint8_t mvdl1[2]{};
    };

    bool prevIntra4x4PredModeFlag[16]{};
    std::uint8_t remIntra4x4PredMode[16]{};

    bool prevIntra8x8PredModeFlag[4]{};
    std::uint8_t remIntra8x8PredMode[4]{};

    std::uint8_t intraChromaPredMode = 0;
    std::vector<Data> mbPartsData;

};


