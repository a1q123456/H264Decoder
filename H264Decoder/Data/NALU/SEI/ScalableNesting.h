#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALUnit.h>
#include <Data/NALU/SEI/SEIMessage.h>

struct DecodingContext;

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
    explicit ScalableNesting(DecodingContext& context, NALUnit nalu, BitstreamReader& reader);
};


