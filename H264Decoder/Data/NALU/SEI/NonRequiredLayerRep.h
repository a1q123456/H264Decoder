#pragma once
#include <IO/BitstreamReader.h>


struct NonRequiredLayerRep
{
    struct InfoEntry
    {
        struct NonRequiredLayerRep
        {
            std::uint8_t nonRequiredLayerRepDependencyId = 0;
            std::uint8_t nonRequiredLayerRepQualityId = 0;

            NonRequiredLayerRep() = default;
            explicit NonRequiredLayerRep(BitstreamReader& reader)
            {
                nonRequiredLayerRepDependencyId = reader.readBits<std::uint8_t, 3>();
                nonRequiredLayerRepQualityId = reader.readBits<std::uint8_t, 4>();
            }
        };

        std::uint8_t entryDependencyId = 0;
        std::uint16_t numNonRequiredLayerRepsMinus1 = 0;
        std::vector<NonRequiredLayerRep> nonRequiredLayerReps;

        InfoEntry() = default;
        explicit InfoEntry(BitstreamReader& reader)
        {
            entryDependencyId = reader.readBits<std::uint8_t, 3>();
            numNonRequiredLayerRepsMinus1 = reader.readExpoGlomb();

            for (auto j = 0; j <= numNonRequiredLayerRepsMinus1; j++)
            {
                nonRequiredLayerReps.emplace_back(reader);
            }
        }
    };

    std::uint32_t numInfoEntriesMinus1 = 0;
    std::vector<InfoEntry> infoEntries;

    NonRequiredLayerRep() = default;
    explicit NonRequiredLayerRep(BitstreamReader& reader)
    {
        numInfoEntriesMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i = numInfoEntriesMinus1; i++)
        {
            infoEntries.emplace_back(reader);
        }
    }
};

