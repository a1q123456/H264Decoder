#pragma once
#include <IO/BitstreamReader.h>


struct LayersNotPresent
{
    std::uint16_t numLayers = 0;
    std::vector<std::uint32_t> layerId;

    LayersNotPresent() = default;
    explicit LayersNotPresent(BitstreamReader& reader)
    {
        numLayers = reader.readExpoGlomb();
        for (auto i = 0; i < numLayers; i++)
        {
            layerId.emplace_back(reader.readExpoGlomb());
        }
    }
};


