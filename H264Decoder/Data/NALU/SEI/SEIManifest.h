#pragma once
#include <IO/BitstreamReader.h>


struct SEIManifest
{
    struct ManifestSEIMsgType
    {
        std::uint16_t manifestSEIPayloadType = 0;
        std::uint8_t manifestSEIDescription = 0;

        ManifestSEIMsgType() = default;
        explicit ManifestSEIMsgType(BitstreamReader& reader)
        {
            manifestSEIPayloadType = reader.readBits<std::uint16_t, 16>();
            manifestSEIDescription = reader.readBits<std::uint8_t, 8>();
        }
    };

    std::uint16_t manifestNumSEIMsgTypes = 0;
    std::vector<ManifestSEIMsgType> manifestSEIMsgTypes;

    SEIManifest() = default;
    explicit SEIManifest(BitstreamReader& reader)
    {
        for (auto i = 0; i < manifestNumSEIMsgTypes; i++)
        {
            manifestSEIMsgTypes.emplace_back(reader);
        }
    }
};


