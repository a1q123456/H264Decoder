#pragma once
#include <IO/BitstreamReader.h>

struct UserDataUnregistered
{
    std::uint8_t uuidIsoIec11578[16] = { 0 };
    std::vector<Byte> userDataPayloadByte;

    UserDataUnregistered() = default;
    explicit UserDataUnregistered(BitstreamReader& reader, int payloadSize)
    {
        for (int i = 0; i < 16; i++)
        {
            uuidIsoIec11578[i] = reader.readBits<std::uint8_t, 8>();
        }
        for (int i = 16; i < payloadSize; i++)
        {
            userDataPayloadByte.emplace_back(reader.readBits<std::uint8_t, 8>());
        }
    }
};


