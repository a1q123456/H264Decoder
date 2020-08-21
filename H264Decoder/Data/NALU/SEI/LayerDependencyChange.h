#pragma once
#include <IO/BitstreamReader.h>


struct LayerDependencyChange
{
    struct Layer
    {
        std::uint16_t layerId = 0;
        bool layerDependencyInfoPresentFlag = false;

        std::uint16_t numDirectlyDependentLayers = 0;
        std::vector<std::uint16_t> directlyDependentLayerIdDeltaMinus1;

        std::uint16_t layerDependencyInfoSrcLayerIdDeltaMinsu1 = 0;

        Layer() = default;
        explicit Layer(BitstreamReader& reader)
        {
            layerId = reader.readExpoGlomb();
            layerDependencyInfoPresentFlag = reader.readBits<bool, 1>();
            if (layerDependencyInfoPresentFlag)
            {
                numDirectlyDependentLayers = reader.readExpoGlomb();
                for (auto j = 0; j < numDirectlyDependentLayers; j++)
                {
                    directlyDependentLayerIdDeltaMinus1.emplace_back(reader.readExpoGlomb());
                }
            }
            else
            {
                layerDependencyInfoSrcLayerIdDeltaMinsu1 = reader.readExpoGlomb();
            }
        }
    };

    std::uint16_t numLayersMinus1 = 0;
    std::vector<Layer> layers;

    LayerDependencyChange() = default;
    explicit LayerDependencyChange(BitstreamReader& reader)
    {
        numLayersMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= numLayersMinus1; i++)
        {
            layers.emplace_back(reader);
        }
    }
};


