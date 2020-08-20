#pragma once
#include <IO/BitstreamReader.h>


struct NonRequiredViewComponent
{
    struct InfoEntry
    {
        std::uint32_t viewOrderIndex = 0;
        std::uint32_t numNonRequiredViewComponentsMinus1 = 0;
        std::vector<std::uint32_t> indexDeltaMinus1;

        InfoEntry() = default;
        explicit InfoEntry(BitstreamReader& reader)
        {
            viewOrderIndex = reader.readExpoGlomb();
            numNonRequiredViewComponentsMinus1 = reader.readExpoGlomb();
            for (auto j = 0; j <= numNonRequiredViewComponentsMinus1; j++)
            {
                indexDeltaMinus1.emplace_back(reader.readExpoGlomb());
            }
        }
    };
    std::uint32_t numInfoEntries = 0;
    std::vector<InfoEntry> infoEntries;

    NonRequiredViewComponent() = default;
    explicit NonRequiredViewComponent(BitstreamReader& reader)
    {
        numInfoEntries = reader.readExpoGlomb();
        for (auto i = 0; i <= numInfoEntries; i++)
        {
            infoEntries.emplace_back(reader);
        }
    }
};

