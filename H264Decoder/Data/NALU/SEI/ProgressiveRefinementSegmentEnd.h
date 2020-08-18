#pragma once
#include <IO/BitstreamReader.h>

struct ProgressiveRefinementSegmentEnd
{
    std::uint8_t progressiveRefinementId = 0;

    ProgressiveRefinementSegmentEnd() = default;
    explicit ProgressiveRefinementSegmentEnd(BitstreamReader& reader);
};

