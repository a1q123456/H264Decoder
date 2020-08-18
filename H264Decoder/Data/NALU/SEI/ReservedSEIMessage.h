#pragma once
#include <IO/BitstreamReader.h>


struct ReservedSEIMessage
{
    std::vector<Byte> reservedSEIMessagePayloadBytes;

    ReservedSEIMessage() = default;
    explicit ReservedSEIMessage(BitstreamReader& reader, int payloadSize)
    {
        for (auto i = 0; i < payloadSize; i++)
        {
            reservedSEIMessagePayloadBytes.emplace_back(reader.readBits<std::uint8_t, 8>());
        }
    }
};



