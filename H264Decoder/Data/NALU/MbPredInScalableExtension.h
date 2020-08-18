#pragma once
#include <IO/BitstreamReader.h>


struct MbPredInScalableExtension
{
    struct Data
    {
        bool motionPredictionFlagl0 = false;
        bool motionPredictionFlagl1 = false;

        std::uint8_t refIdxl0 = 0;
        std::uint8_t refIdxl1 = 0;

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


