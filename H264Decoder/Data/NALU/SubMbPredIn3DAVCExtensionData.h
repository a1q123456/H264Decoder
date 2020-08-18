#pragma once
#include <IO/BitstreamReader.h>


struct SubMbPredIn3DAVCExtensionData
{
    std::uint8_t subMbType = 0;
    std::uint8_t refIdxl0 = 0;
    bool bvspFlagl0 = false;

    std::uint8_t refIdxl1 = 0;
    bool bvspFlagl1 = false;

    std::vector<std::uint8_t[2]> mvdl0;
    std::vector<std::uint8_t[2]> mvdl1;

};


