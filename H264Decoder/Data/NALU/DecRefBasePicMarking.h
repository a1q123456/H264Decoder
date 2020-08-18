#pragma once
#include <IO/BitstreamReader.h>


struct DecRefBasePicMarking
{
    bool adaptiveRefBasePicMarkingModeFlag = false;

    std::vector<AdaptiveRefBasePicMarkingMode> adaptiveRefBasePicMarkingMode;
};


