#pragma once
#include <IO/BitstreamReader.h>


struct ParallelDecodingInfo
{
    std::uint32_t seqParameterSetId = 0;
    std::vector<std::vector<std::uint32_t>> pdiInitDelayAnchorMinus2L0;
    std::vector<std::vector<std::uint32_t>> pdiInitDelayAnchorMinus2L1;

    std::vector<std::vector<std::uint32_t>> pdiInitDelayNonAnchorMinus2L0;
    std::vector<std::vector<std::uint32_t>> pdiInitDelayNonAnchorMinus2L1;

    ParallelDecodingInfo() = default;
    explicit ParallelDecodingInfo(DecodingContext& dc, BitstreamReader& reader, NALUnit& currentNalUint)
    {
        seqParameterSetId = reader.readExpoGlomb();
        auto&& subsetSps = dc.findSubsetSPS(seqParameterSetId);
        pdiInitDelayAnchorMinus2L0.resize(subsetSps.seqParameterSetMVCExtension.numViewsMinus1);
        pdiInitDelayAnchorMinus2L1.resize(subsetSps.seqParameterSetMVCExtension.numViewsMinus1);
        pdiInitDelayNonAnchorMinus2L0.resize(subsetSps.seqParameterSetMVCExtension.numViewsMinus1);
        pdiInitDelayNonAnchorMinus2L1.resize(subsetSps.seqParameterSetMVCExtension.numViewsMinus1);
        for (auto i = 1; i <= subsetSps.seqParameterSetMVCExtension.numViewsMinus1; i++)
        {
            if (currentNalUint.nalUnitHeaderMvcExtension.anchorPicFlag)
            {
                pdiInitDelayAnchorMinus2L0[i].resize(subsetSps.seqParameterSetMVCExtension.anchorRefs[i].numAnchorRefsL0);
                for (auto j = 0; j <= subsetSps.seqParameterSetMVCExtension.anchorRefs[i].numAnchorRefsL0; j++)
                {
                    pdiInitDelayAnchorMinus2L0[i][j] = reader.readExpoGlomb();
                }
                pdiInitDelayAnchorMinus2L1[i].resize(subsetSps.seqParameterSetMVCExtension.anchorRefs[i].numAnchorRefsL1);
                for (auto j = 0; j <= subsetSps.seqParameterSetMVCExtension.anchorRefs[i].numAnchorRefsL0; j++)
                {
                    pdiInitDelayAnchorMinus2L1[i][j] = reader.readExpoGlomb();
                }
            }
            else
            {
                pdiInitDelayNonAnchorMinus2L0[i].resize(subsetSps.seqParameterSetMVCExtension.nonAnchorRefs[i].numAnchorRefsL0);
                for (auto j = 0; j <= subsetSps.seqParameterSetMVCExtension.nonAnchorRefs[i].numAnchorRefsL0; j++)
                {
                    pdiInitDelayNonAnchorMinus2L0[i][j] = reader.readExpoGlomb();
                }
                pdiInitDelayNonAnchorMinus2L1[i].resize(subsetSps.seqParameterSetMVCExtension.nonAnchorRefs[i].numAnchorRefsL1);
                for (auto j = 0; j <= subsetSps.seqParameterSetMVCExtension.anchorRefs[i].numAnchorRefsL0; j++)
                {
                    pdiInitDelayNonAnchorMinus2L1[i][j] = reader.readExpoGlomb();
                }
            }
        }
    }
};


