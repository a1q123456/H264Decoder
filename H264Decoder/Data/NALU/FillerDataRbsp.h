#pragma once
#include <IO/BitstreamReader.h>


struct FillerDataRbsp
{
    std::vector<std::uint8_t> ffBytes;

    RbspTrailingBits rbspTrailingBits;

    FillerDataRbsp() = default;
    explicit FillerDataRbsp(BitstreamReader& reader)
    {
        while (reader.nextBits<std::uint8_t, 8>() == 0xFF)
        {
            ffBytes.emplace_back(reader.readBits<std::uint8_t, 8>());
        }
        rbspTrailingBits = RbspTrailingBits{ reader };
    }
};


