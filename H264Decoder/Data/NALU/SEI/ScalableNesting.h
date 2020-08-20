#pragma once
#include <IO/BitstreamReader.h>


struct ScalableNesting
{
    struct LayerRepresentation
    {
        std::uint8_t seiDependencyId = 0;
        std::uint8_t seiQualityId = 0;

        LayerRepresentation() = default;
        explicit LayerRepresentation(BitstreamReader& reader)
        {
            seiDependencyId = reader.readBits<std::uint8_t, 3>();
            seiQualityId = reader.readBits<std::uint8_t, 4>();
        }
    };

    bool allLayerRepresentationsInAuFlag = false;
    std::uint32_t numLayerRepresentationsMinus1 = 0;
    std::vector<LayerRepresentation> layerRepresentations;
    std::uint8_t seiTemporalId = 0;

    std::uint8_t seiNestingZeroBit = 0;

    std::vector<SEIMessage> seiMessage;

    ScalableNesting() = default;
    explicit ScalableNesting(BitstreamReader& reader)
    {
        allLayerRepresentationsInAuFlag = reader.readBits<bool, 1>();
        if (!allLayerRepresentationsInAuFlag)
        {
            numLayerRepresentationsMinus1 = reader.readExpoGlomb();
            for (auto i = 0; i <= numLayerRepresentationsMinus1; i++)
            {
                layerRepresentations.emplace_back(reader);
            }
            seiTemporalId = reader.readBits<std::uint8_t, 3>();
        }
        while (!reader.byteAligned())
        {
            seiNestingZeroBit = reader.readBits<std::uint8_t, 1>();
            if (seiNestingZeroBit != 0)
            {
                throw std::runtime_error("not supported");
            }
        }
        do
        {
            // TODO sei message
        } while (reader.moreData());
    }
};


