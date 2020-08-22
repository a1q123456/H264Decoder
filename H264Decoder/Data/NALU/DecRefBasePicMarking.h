#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\AdaptiveRefBasePicMarkingMode.h>


struct DecRefBasePicMarking
{
    bool adaptiveRefBasePicMarkingModeFlag = false;

    std::vector<AdaptiveRefBasePicMarkingMode> adaptiveRefBasePicMarkingMode;
};


