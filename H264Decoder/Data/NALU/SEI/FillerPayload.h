#pragma once
#include <IO/BitstreamReader.h>


struct FillerPayload
{
    std::vector<std::uint8_t> ffBytes;

    FillerPayload() = default;
    explicit FillerPayload(BitstreamReader& reader, int payloadSize)
    {
        for (auto k = 0; k < payloadSize; k++)
        {
            ffBytes.emplace_back(reader.readBits<std::uint8_t, 8>());
        }
    }
};


