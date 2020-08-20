#pragma once
#include <IO/BitstreamReader.h>


struct PriorityLayerInfo
{
    std::uint8_t prDependencyId = 0;
    std::uint8_t numPriorityIds = 0;

    std::vector<std::uint8_t> altPriorityIds;

    PriorityLayerInfo() = default;
    explicit PriorityLayerInfo(BitstreamReader& reader)
    {
        prDependencyId = reader.readBits<std::uint8_t, 3>();
        numPriorityIds = reader.readBits<std::uint8_t, 4>();
        for (auto i = 0; i <= numPriorityIds; i++)
        {
            altPriorityIds.emplace_back(reader.readBits<std::uint8_t, 6>());
        }
    }
};


