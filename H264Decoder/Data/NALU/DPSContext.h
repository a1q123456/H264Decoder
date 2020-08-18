#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\DPSRbsp.h>


struct DPSContext
{
    DPSRbsp dpsRbsp;


    std::vector<std::vector<std::int8_t>> zNearSign;
    std::vector<std::vector<std::int8_t>> zFarSign;
    std::vector<std::vector<std::uint32_t>> zNearExp;
    std::vector<std::vector<std::uint32_t>> zFarExp;
    std::vector<std::vector<std::uint32_t>> zNearMantissa;
    std::vector<std::vector<std::uint32_t>> zFarMantissa;
    std::vector<std::vector<std::uint32_t>> zNearManLen;
    std::vector<std::vector<std::uint32_t>> zFarManLen;

};


