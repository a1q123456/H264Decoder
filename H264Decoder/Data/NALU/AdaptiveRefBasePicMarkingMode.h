#pragma once
#include <IO/BitstreamReader.h>


struct AdaptiveRefBasePicMarkingMode
{
    std::uint8_t memoryManagementBaseControlOperation = 0;
    std::uint8_t differenceOfBasePicNumsMinus1 = 0;
    std::uint8_t longTermBasePicNum = 0;
};


