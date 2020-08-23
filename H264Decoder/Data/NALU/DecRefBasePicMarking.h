#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\AdaptiveRefBasePicMarkingMode.h>


struct DecRefBasePicMarking
{
    bool adaptiveRefBasePicMarkingModeFlag = false;

    std::vector<AdaptiveRefBasePicMarkingMode> adaptiveRefBasePicMarkingMode;

    DecRefBasePicMarking() = default;
    explicit DecRefBasePicMarking(BitstreamReader& reader)
    {
        adaptiveRefBasePicMarkingModeFlag = reader.readBits<bool, 1>();
        if (adaptiveRefBasePicMarkingModeFlag)
        {
            while (adaptiveRefBasePicMarkingMode.emplace_back(reader).memoryManagementBaseControlOperation != 0)
            {
            }
        }
    }
};


