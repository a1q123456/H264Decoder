#pragma once
#include <IO/BitstreamReader.h>


struct AdaptiveRefBasePicMarkingMode
{
    std::uint8_t memoryManagementBaseControlOperation = 0;
    std::uint8_t differenceOfBasePicNumsMinus1 = 0;
    std::uint8_t longTermBasePicNum = 0;

    AdaptiveRefBasePicMarkingMode() = default;
    explicit AdaptiveRefBasePicMarkingMode(BitstreamReader& reader)
    {
        memoryManagementBaseControlOperation = reader.readExpoGlomb();
        if (memoryManagementBaseControlOperation == 1)
        {
            differenceOfBasePicNumsMinus1 = reader.readExpoGlomb();
        }
        if (memoryManagementBaseControlOperation == 2)
        {
            longTermBasePicNum = reader.readExpoGlomb();
        }
    }
};


