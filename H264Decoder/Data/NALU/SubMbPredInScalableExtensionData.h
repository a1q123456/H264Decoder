#pragma once
#include <IO/BitstreamReader.h>


struct SubMbPredInScalableExtensionData
{
    std::uint8_t subMbType = 0;

    bool motionPredictionFlagl0 = false;
    bool motionPredictionFlagl1 = false;

    std::uint8_t refIdxl0 = 0;
    std::uint8_t refIdxl1 = 0;

    std::vector<std::uint8_t[2]> mvdl0;
    std::vector<std::uint8_t[2]> mvdl1;

};


