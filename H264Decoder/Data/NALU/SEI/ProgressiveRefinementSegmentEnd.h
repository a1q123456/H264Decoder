#pragma once
#include <IO/BitstreamReader.h>

struct ProgressiveRefinementSegmentEnd
{
    std::uint16_t progressiveRefinementId = 0;

    ProgressiveRefinementSegmentEnd() = default;
    explicit ProgressiveRefinementSegmentEnd(BitstreamReader& reader);
};

