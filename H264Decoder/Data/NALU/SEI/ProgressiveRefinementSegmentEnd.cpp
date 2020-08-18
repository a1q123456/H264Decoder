#include "pch.h"
#include "ProgressiveRefinementSegmentEnd.h"

ProgressiveRefinementSegmentEnd::ProgressiveRefinementSegmentEnd(BitstreamReader& reader)
{
    progressiveRefinementId = reader.readExpoGlomb();
}
