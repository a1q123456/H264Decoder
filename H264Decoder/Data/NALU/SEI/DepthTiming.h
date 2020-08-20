#pragma once
#include <IO/BitstreamReader.h>


struct DepthTiming
{
    bool perViewDepthTimingFlag = false;
    std::vector<DepthTimingOffset> depthTimingOffsets;
    DepthTimingOffset depthTimingOffset;

    DepthTiming() = default;
    explicit DepthTiming(DecodingContext& ctx, BitstreamReader& reader)
    {
        perViewDepthTimingFlag = reader.readBits<bool, 1>();
        if (perViewDepthTimingFlag)
        {
            for (auto i = 0; i < ctx.currentDPS().dpsRbsp.numDepthViewsMinus1 + 1; i++)
            {
                depthTimingOffsets.emplace_back(reader);
            }
        }
        else
        {
            depthTimingOffset = DepthTimingOffset{ reader };
        }
    }
};


