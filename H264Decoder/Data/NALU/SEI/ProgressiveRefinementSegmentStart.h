#pragma once
#include <IO/BitstreamReader.h>

struct ProgressiveRefinementSegmentStart
{
    std::uint8_t progressiveRefinementId = 0;

    ProgressiveRefinementSegmentStart() = default;
    explicit ProgressiveRefinementSegmentStart(BitstreamReader& reader)
    {
        progressiveRefinementId = reader.readExpoGlomb();
    }
};


