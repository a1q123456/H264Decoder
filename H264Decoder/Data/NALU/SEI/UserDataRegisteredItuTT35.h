#pragma once
#include <IO/BitstreamReader.h>


struct UserDataRegisteredItuTT35
{
    Byte ituTT35CountryCode = 0;
    Byte ituTT35CountryCodeExtensionByte = 0;

    std::vector<Byte> ituTT35PayloadByte;

    UserDataRegisteredItuTT35() = default;

    explicit UserDataRegisteredItuTT35(BitstreamReader& reader, int payloadSize)
    {
        ituTT35CountryCode = reader.readBits<std::uint8_t, 8>();
        auto i = 0;
        if (ituTT35CountryCode != 0xFF)
        {
            i = 1;
        }
        else
        {
            ituTT35CountryCodeExtensionByte = reader.readBits<std::uint8_t, 8>();
            i = 2;
        }
        do
        {
            ituTT35PayloadByte.emplace_back(reader.readBits<std::uint8_t, 8>());
            i++;
        } while (i < payloadSize);

    }
};

