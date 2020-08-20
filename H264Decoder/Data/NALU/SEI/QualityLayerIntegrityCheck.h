#pragma once
#include <IO/BitstreamReader.h>


struct QualityLayerIntegrityCheck
{
    struct InfoEntry
    {
        std::uint8_t entryDependencyId = 0;
        std::uint16_t qualityLayerCrc = 0;

        InfoEntry() = default;
        explicit InfoEntry(BitstreamReader& reader)
        {
            entryDependencyId = reader.readBits<std::uint8_t, 3>();
            qualityLayerCrc = reader.readBits<std::uint16_t, 16>();
        }
    };

    std::uint32_t numInfoEntriesMinus1 = 0;
    std::vector<InfoEntry> infoEntries;

    QualityLayerIntegrityCheck() = default;
    explicit QualityLayerIntegrityCheck(BitstreamReader& reader)
    {
        numInfoEntriesMinus1 = reader.readExpoGlomb();
        infoEntries.emplace_back(reader);
    }
};

