#pragma once
#include <IO/BitstreamReader.h>


struct ViewDependencyChange
{
    struct RefFlags
    {
        std::vector<BoolType> L0Flags;
        std::vector<BoolType> L1Flags;

    };

    std::uint32_t seqParameterSetId = 0;
    bool anchorUpdateFlag = false;
    bool nonAnchorUpdateFlag = false;
    std::vector<RefFlags> anchorRefFlags;
    std::vector<RefFlags> nonAnchorRefFlags;

    ViewDependencyChange() = default;
    explicit ViewDependencyChange(DecodingContext& ctx, BitstreamReader& reader)
    {
        seqParameterSetId = reader.readExpoGlomb();
        anchorUpdateFlag = reader.readBits<bool, 1>();
        nonAnchorUpdateFlag = reader.readBits<bool, 1>();

        auto sps = ctx.findSubsetSPS(seqParameterSetId);

        if (anchorUpdateFlag)
        {
            anchorRefFlags.resize(sps.seqParameterSetMVCExtension.numViewsMinus1 + 1);
            for (auto i = 1; i <= sps.seqParameterSetMVCExtension.numViewsMinus1; i++)
            {
                anchorRefFlags[i].L0Flags.resize(sps.seqParameterSetMVCExtension.anchorRefs[i].numAnchorRefsL0);
                for (auto j = 0; j < sps.seqParameterSetMVCExtension.anchorRefs[i].numAnchorRefsL0; j++)
                {
                    anchorRefFlags[i].L0Flags[j] = reader.readBits<std::uint8_t, 1>();
                }
                anchorRefFlags[i].L1Flags.resize(sps.seqParameterSetMVCExtension.anchorRefs[i].numAnchorRefsL1);
                for (auto j = 0; j < sps.seqParameterSetMVCExtension.anchorRefs[i].numAnchorRefsL1; j++)
                {
                    anchorRefFlags[i].L1Flags[j] = reader.readBits<std::uint8_t, 1>();
                }
            }
        }
        if (nonAnchorUpdateFlag)
        {
            nonAnchorRefFlags.resize(sps.seqParameterSetMVCExtension.numViewsMinus1 + 1);
            for (auto i = 1; i <= sps.seqParameterSetMVCExtension.numViewsMinus1; i++)
            {
                nonAnchorRefFlags[i].L0Flags.resize(sps.seqParameterSetMVCExtension.nonAnchorRefs[i].numAnchorRefsL0);
                for (auto j = 0; j < sps.seqParameterSetMVCExtension.nonAnchorRefs[i].numAnchorRefsL0; j++)
                {
                    nonAnchorRefFlags[i].L0Flags[j] = reader.readBits<std::uint8_t, 1>();
                }
                nonAnchorRefFlags[i].L1Flags.resize(sps.seqParameterSetMVCExtension.nonAnchorRefs[i].numAnchorRefsL1);
                for (auto j = 0; j < sps.seqParameterSetMVCExtension.nonAnchorRefs[i].numAnchorRefsL1; j++)
                {
                    nonAnchorRefFlags[i].L1Flags[j] = reader.readBits<std::uint8_t, 1>();
                }
            }
        }
    }
};



