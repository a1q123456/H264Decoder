#pragma once
#include <IO/BitstreamReader.h>

struct MotionConstrainedSliceGroupSet
{
    std::uint16_t numSliceGroupsInSetMinus1 = 0;
    std::vector<std::uint16_t> sliceGroupIds;

    bool exactSampleValueMatchFlag = false;
    bool panScanRectFlag = false;
    std::uint16_t panScanRectId = 0;

    MotionConstrainedSliceGroupSet() = default;
    explicit MotionConstrainedSliceGroupSet(DecodingContext& ctx, BitstreamReader& reader)
    {
        numSliceGroupsInSetMinus1 = reader.readExpoGlomb();
        if (numSliceGroupsInSetMinus1 > 0)
        {
            for (auto i = 0; i <= numSliceGroupsInSetMinus1; i++)
            {
                sliceGroupIds.emplace_back(reader.readBits<std::uint16_t>(static_cast<int>(std::ceil(std::log2(ctx.currentPPS().numSliceGroupsMinus1 + 1)))));
            }
        }
        exactSampleValueMatchFlag = reader.readBits<bool, 1>();
        panScanRectFlag = reader.readBits<bool, 1>();
        if (panScanRectFlag)
        {
            panScanRectId = reader.readExpoGlomb();
        }
    }

};

