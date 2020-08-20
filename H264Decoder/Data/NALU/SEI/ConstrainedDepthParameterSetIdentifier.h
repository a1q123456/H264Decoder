#pragma once
#include <IO/BitstreamReader.h>

struct ConstrainedDepthParameterSetIdentifier
{
    std::uint32_t maxDpsId = 0;
    std::uint32_t maxDpsIdDiff = 0;

    ConstrainedDepthParameterSetIdentifier() = default;
    explicit ConstrainedDepthParameterSetIdentifier(BitstreamReader& reader)
    {
        maxDpsId = reader.readExpoGlomb();
        maxDpsIdDiff = reader.readExpoGlomb();
    }
};


