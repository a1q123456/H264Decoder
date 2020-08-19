#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/SEI/SEIType.h>
#include <Data\NALU\SEI\BufferingPeriod.h>
#include <Data\NALU\SEI\PicTiming.h>
#include <Data\NALU\SEI\PanScanRect.h>
#include <Data\NALU\SEI\FillerPayload.h>
#include <Data\NALU\SEI\UserDataRegisteredItuTT35.h>
#include <Data\NALU\SEI\UserDataUnregistered.h>
#include <Data\NALU\SEI\RecoveryPoint.h>
#include <Data\NALU\SEI\DecRefPicMarkingRepetition.h>
#include <Data\NALU\SEI\SparePic.h>
#include <Data\NALU\SEI\SceneInfo.h>
#include <Data\NALU\SEI\SubSeqInfo.h>
#include <Data\NALU\SEI\SubSeqLayerCharacteristics.h>
#include <Data\NALU\SEI\SubSeqCharacteristics.h>
#include <Data\NALU\SEI\FullFrameFreeze.h>
#include <Data\NALU\SEI\FullFrameFreezeRelease.h>
#include <Data\NALU\SEI\FullFrameSnapshot.h>
#include <Data\NALU\SEI\ProgressiveRefinementSegmentStart.h>
#include <Data\NALU\SEI\ProgressiveRefinementSegmentEnd.h>
#include <Data\NALU\SEI\MotionConstrainedSliceGroupSet.h>
#include <Data\NALU\SEI\FilmGrainCharacteristics.h>
#include <Data\NALU\SEI\DeblockingFilterDisplayPreference.h>
#include <Data\NALU\SEI\StereoVideoInfo.h>
#include <Data\NALU\SEI\PostFilterHint.h>
#include <Data\NALU\SEI\ToneMappingInfo.h>
#include <Data\NALU\SEI\ScalabilityInfo.h>
#include <Data\NALU\SEI\SubPicScalableLayer.h>
#include <Data\NALU\SEI\NonRequiredLayerRep.h>
#include <Data\NALU\SEI\PriorityLayerInfo.h>
#include <Data\NALU\SEI\LayersNotPresent.h>
#include <Data\NALU\SEI\LayerDependencyChange.h>
#include <Data\NALU\SEI\ScalableNesting.h>
#include <Data\NALU\SEI\BaseLayerTemporalHrd.h>
#include <Data\NALU\SEI\QualityLayerIntegrityCheck.h>
#include <Data\NALU\SEI\RedundantPicProperty.h>
#include <Data\NALU\SEI\Tl0DepRepIndex.h>
#include <Data\NALU\SEI\TlSwitchingPoint.h>
#include <Data\NALU\SEI\ParallelDecodingInfo.h>
#include <Data\NALU\SEI\MvcScalableNesting.h>
#include <Data\NALU\SEI\ViewScalabilityInfo.h>
#include <Data\NALU\SEI\MultiviewSceneInfo.h>
#include <Data\NALU\SEI\MultiviewAcquisitionInfo.h>
#include <Data\NALU\SEI\NonRequiredViewComponent.h>
#include <Data\NALU\SEI\ViewDependencyChange.h>
#include <Data\NALU\SEI\OperationPointsNotPresent.h>
#include <Data\NALU\SEI\BaseViewTemporalHrd.h>
#include <Data\NALU\SEI\FramePackingArrangement.h>
#include <Data\NALU\SEI\MultiviewViewPosition.h>
#include <Data\NALU\SEI\DisplayOrientation.h>
#include <Data\NALU\SEI\MvcdScalableNesting.h>
#include <Data\NALU\SEI\MvcdViewScalabilityInfo.h>
#include <Data\NALU\SEI\DepthRepresentationInfo.h>
#include <Data\NALU\SEI\ThreeDimensionalReferenceDisplaysInfo.h>
#include <Data\NALU\SEI\DepthTiming.h>
#include <Data\NALU\SEI\DepthSamplingInfo.h>
#include <Data\NALU\SEI\ConstrainedDepthParameterSetIdentifier.h>
#include <Data\NALU\SEI\MasteringDisplayColourVolume.h>
#include <Data\NALU\SEI\ReservedSEIMessage.h>
#include <Data\NALU\SEI\SEIType.h>
#include <Data\RealValue.h>

struct SubPicScalableLayer
{
    std::uint32_t layerId = 0;

    SubPicScalableLayer() = default;
    explicit SubPicScalableLayer(BitstreamReader& reader)
    {
        layerId = reader.readExpoGlomb();
    }
};

struct NonRequiredLayerRep
{
    struct InfoEntry
    {
        struct NonRequiredLayerRep
        {
            std::uint8_t nonRequiredLayerRepDependencyId = 0;
            std::uint8_t nonRequiredLayerRepQualityId = 0;

            NonRequiredLayerRep() = default;
            explicit NonRequiredLayerRep(BitstreamReader& reader)
            {
                nonRequiredLayerRepDependencyId = reader.readBits<std::uint8_t, 3>();
                nonRequiredLayerRepQualityId = reader.readBits<std::uint8_t, 4>();
            }
        };

        std::uint8_t entryDependencyId = 0;
        std::uint32_t numNonRequiredLayerRepsMinus1 = 0;
        std::vector<NonRequiredLayerRep> nonRequiredLayerReps;

        InfoEntry() = default;
        explicit InfoEntry(BitstreamReader& reader)
        {
            entryDependencyId = reader.readBits<std::uint8_t, 3>();
            numNonRequiredLayerRepsMinus1 = reader.readExpoGlomb();

            for (auto j = 0; j <= numNonRequiredLayerRepsMinus1; j++)
            {
                nonRequiredLayerReps.emplace_back(reader);
            }
        }
    };

    std::uint32_t numInfoEntriesMinus1 = 0;
    std::vector<InfoEntry> infoEntries;

    NonRequiredLayerRep() = default;
    explicit NonRequiredLayerRep(BitstreamReader& reader)
    {
        numInfoEntriesMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i = numInfoEntriesMinus1; i++)
        {
            infoEntries.emplace_back(reader);
        }
    }
};

struct PriorityLayerInfo
{
    std::uint8_t prDependencyId = 0;
    std::uint8_t numPriorityIds = 0;

    std::vector<std::uint8_t> altPriorityIds;

    PriorityLayerInfo() = default;
    explicit PriorityLayerInfo(BitstreamReader& reader)
    {
        prDependencyId = reader.readBits<std::uint8_t, 3>();
        numPriorityIds = reader.readBits<std::uint8_t, 4>();
        for (auto i = 0; i <= numPriorityIds; i++)
        {
            altPriorityIds.emplace_back(reader.readBits<std::uint8_t, 6>());
        }
    }
};

struct LayersNotPresent
{
    std::uint32_t numLayers = 0;
    std::vector<std::uint32_t> layerId;

    LayersNotPresent() = default;
    explicit LayersNotPresent(BitstreamReader& reader)
    {
        numLayers = reader.readExpoGlomb();
        for (auto i = 0; i < numLayers; i++)
        {
            layerId.emplace_back(reader.readExpoGlomb());
        }
    }
};

struct LayerDependencyChange
{
    struct Layer
    {
        std::uint32_t layerId = 0;
        bool layerDependencyInfoPresentFlag = false;

        std::uint32_t numDirectlyDependentLayers = 0;
        std::vector<std::uint32_t> directlyDependentLayerIdDeltaMinus1;

        std::uint32_t layerDependencyInfoSrcLayerIdDeltaMinsu1 = 0;

        Layer() = default;
        explicit Layer(BitstreamReader& reader)
        {
            layerId = reader.readExpoGlomb();
            layerDependencyInfoPresentFlag = reader.readBits<bool, 1>();
            if (layerDependencyInfoPresentFlag)
            {
                numDirectlyDependentLayers = reader.readExpoGlomb();
                for (auto j = 0; j < numDirectlyDependentLayers; j++)
                {
                    directlyDependentLayerIdDeltaMinus1.emplace_back(reader.readExpoGlomb());
                }
            }
            else
            {
                layerDependencyInfoSrcLayerIdDeltaMinsu1 = reader.readExpoGlomb();
            }
        }
    };

    std::uint32_t numLayersMinus1 = 0;
    std::vector<Layer> layers;

    LayerDependencyChange() = default;
    explicit LayerDependencyChange(BitstreamReader& reader)
    {
        numLayersMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= numLayersMinus1; i++)
        {
            layers.emplace_back(reader);
        }
    }
};

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
    explicit ScalableNesting(BitstreamReader& reader)
    {
        allLayerRepresentationsInAuFlag = reader.readBits<bool, 1>();
        if (!allLayerRepresentationsInAuFlag)
        {
            numLayerRepresentationsMinus1 = reader.readExpoGlomb();
            for (auto i = 0; i <= numLayerRepresentationsMinus1; i++)
            {
                layerRepresentations.emplace_back(reader);
            }
            seiTemporalId = reader.readBits<std::uint8_t, 3>();
        }
        while (!reader.byteAligned())
        {
            seiNestingZeroBit = reader.readBits<std::uint8_t, 1>();
            if (seiNestingZeroBit != 0)
            {
                throw std::runtime_error("not supported");
            }
        }
        do
        {
            // TODO sei message
        } while (reader.moreData());
    }
};

struct BaseLayerTemporalHrd
{
    struct TemporalLayer
    {
        std::uint8_t seiTemporalId = 0;
        bool seiTimingInfoPresentFlag = false;

        std::uint32_t seiNumUnitsInTick = 0;
        std::uint32_t seiTimeScale = 0;
        bool seiFixedFrameRateFlag = false;

        bool seiNalHrdParametersPresentFlag = false;
        bool seiVclHrdParametersPresentFlag = false;

        HrdParameters hrdParameters;

        bool seiLowDelayHrdFlag = false;

        bool seiPicStructPresentFlag = false;

        TemporalLayer() = default;
        explicit TemporalLayer(BitstreamReader& reader)
        {
            seiTemporalId = reader.readBits<std::uint8_t, 3>();
            seiTimingInfoPresentFlag = reader.readBits<bool, 1>();

            if (seiTimingInfoPresentFlag)
            {
                seiNumUnitsInTick = reader.readBits<std::uint32_t, 32>();
                seiTimeScale = reader.readBits<std::uint32_t, 32>();
                seiFixedFrameRateFlag = reader.readBits<bool, 1>();
            }
            seiNalHrdParametersPresentFlag = reader.readBits<bool, 1>();
            if (seiNalHrdParametersPresentFlag)
            {
                hrdParameters = HrdParameters{ reader };
            }
            seiVclHrdParametersPresentFlag = reader.readBits<bool, 1>();
            if (seiVclHrdParametersPresentFlag)
            {
                hrdParameters = HrdParameters{ reader };
            }
            if (seiNalHrdParametersPresentFlag || seiVclHrdParametersPresentFlag)
            {
                seiLowDelayHrdFlag = reader.readBits<bool, 1>();
            }
            seiPicStructPresentFlag = reader.readBits<bool, 1>();
        }
    };

    std::uint32_t numOfTemporalLayersInBaseLayerMinus1 = 0;
    std::vector<TemporalLayer> temporalLayersInBaseLayer;

    BaseLayerTemporalHrd() = default;
    explicit BaseLayerTemporalHrd(BitstreamReader& reader)
    {
        numOfTemporalLayersInBaseLayerMinus1 = reader.readExpoGlomb();
        temporalLayersInBaseLayer.emplace_back(reader);
    }

};

struct QualityLayerIntegrityCheck
{
    struct InfoEntry
    {
        std::uint8_t entryDependencyId = 0;
        std::uint16_t qualityLayerCrc = 0;

        InfoEntry() = default;
        explicit InfoEntry(BitstreamReader& reader)
        {
            entryDependencyId = reader.readBits<std::uint8_t, 3>();
            qualityLayerCrc = reader.readBits<std::uint16_t, 16>();
        }
    };

    std::uint32_t numInfoEntriesMinus1 = 0;
    std::vector<InfoEntry> infoEntries;

    QualityLayerIntegrityCheck() = default;
    explicit QualityLayerIntegrityCheck(BitstreamReader& reader)
    {
        numInfoEntriesMinus1 = reader.readExpoGlomb();
        infoEntries.emplace_back(reader);
    }
};

struct RedundantPicProperty
{
    struct DId
    {
        struct QId
        {
            struct RedundantPic
            {
                std::uint32_t redundantPicCntMinus1 = 0;
                bool picMatchFlag = false;

                bool mbTypeMatchFlag = false;
                bool motionMatchFlag = false;
                bool residualMatchFlag = false;
                bool intraSamplesMatchFlag = false;

                RedundantPic() = default;
                explicit RedundantPic(BitstreamReader& reader)
                {
                    redundantPicCntMinus1 = reader.readExpoGlomb();
                    picMatchFlag = reader.readBits<bool, 1>();
                    if (!picMatchFlag)
                    {
                        mbTypeMatchFlag = reader.readBits<bool, 1>();
                        motionMatchFlag = reader.readBits<bool, 1>();
                        residualMatchFlag = reader.readBits<bool, 1>();
                        intraSamplesMatchFlag = reader.readBits<bool, 1>();
                    }
                }
            };

            std::uint8_t qualityId = 0;
            std::uint32_t numRedundantPicsMinus1 = 0;
            std::vector<RedundantPic> redundantPics;

            QId() = default;
            explicit QId(BitstreamReader& reader)
            {
                qualityId = reader.readBits<std::uint8_t, 4>();
                numRedundantPicsMinus1 = reader.readExpoGlomb();
                for (auto k = 0; k <= numRedundantPicsMinus1; k++)
                {
                    redundantPics.emplace_back(reader);
                }
                
            }
        };

        std::uint8_t dependencyId = 0;
        std::uint32_t numQIdsMinus1 = 0;
        std::vector<QId> qIds;

        DId() = default;
        explicit DId(BitstreamReader& reader)
        {
            dependencyId = reader.readBits<std::uint8_t, 3>();
            numQIdsMinus1 = reader.readExpoGlomb();
            for (auto j = 0; j <= numQIdsMinus1; j++)
            {
                qIds.emplace_back(reader);
            }
        }
    };

    std::uint32_t numDIdsMinus1 = 0;
    std::vector<DId> dIds;

    RedundantPicProperty() = default;
    explicit RedundantPicProperty(BitstreamReader& reader)
    {
        numDIdsMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= numDIdsMinus1; i++)
        {
            dIds.emplace_back(reader);
        }
    }
};

struct Tl0DepRepIndex
{
    std::uint8_t tl0DepRepIdx = 0;
    std::uint16_t effectiveIdrPicId = 0;

    Tl0DepRepIndex() = default;
    explicit Tl0DepRepIndex(BitstreamReader& reader)
    {
        tl0DepRepIdx = reader.readBits<std::uint8_t, 8>();
        effectiveIdrPicId = reader.readBits<std::uint16_t, 16>();
    }
};

struct TlSwitchingPoint
{
    std::int32_t deltaFrameNum = 0;

    TlSwitchingPoint() = default;
    explicit TlSwitchingPoint(BitstreamReader& reader)
    {
        deltaFrameNum = reader.readSignedExpoGlomb();
    }
};

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

struct MvcScalableNesting
{
    bool operationPointFlag = false;
    bool allViewComponentsInAuFlag = false;
    std::uint32_t numViewComponentsMinus1;

    std::vector<std::uint16_t> seiViewId;

    std::uint32_t numViewComponentsOpMinus1 = 0;
    std::vector<std::uint16_t> seiOpViewId;
    std::uint8_t seiOpTemporalId = 0;

    std::uint8_t seiNestingZeroBit = 0;
    SEIMessage seiMessage;

    MvcScalableNesting() = default;
    explicit MvcScalableNesting(BitstreamReader& reader)
    {
        operationPointFlag = reader.readBits<bool, 1>();
        if (!operationPointFlag)
        {
            allViewComponentsInAuFlag = reader.readBits<bool, 1>();
            if (!allViewComponentsInAuFlag)
            {
                numViewComponentsMinus1 = reader.readExpoGlomb();
                for (auto i = 0; i <= numViewComponentsMinus1; i++)
                {
                    seiViewId.emplace_back(reader.readBits<std::uint16_t, 10>());
                }
            }
        }
        else
        {
            numViewComponentsOpMinus1 = reader.readExpoGlomb();
            for (auto i = 0; i <= numViewComponentsOpMinus1; i++)
            {
                seiOpViewId.emplace_back(reader.readBits<std::uint16_t, 10>());
            }
            seiOpTemporalId = reader.readBits<std::uint8_t, 3>();
        }
        while (!reader.byteAligned())
        {
            reader.readBits<std::uint8_t, 1>();
        }
        // TODO sei message
    }
};

struct ViewScalabilityInfo
{
    struct OperationPoint
    {
        std::uint32_t operationPointId = 0;
        std::uint8_t priorityId = 0;
        std::uint8_t   temporalId = 0;
        std::uint32_t numTargetOutputViewsMinus1 = 0;
        std::vector<std::uint32_t> viewId;

        bool profileLevelInfoPresentFlag = false;
        bool bitrateInfoPresentFlag = false;
        bool frmRateInfoPresentFlag = false;
        bool viewDependencyInfoPresentFlag = false;
        bool parameterSetsInfoPresentFlag = false;
        bool bitstreamRestrictionInfoPresentFlag = false;
        std::uint32_t opProfileLevelIdc = 0;
        std::uint16_t avgBitrate = 0;
        std::uint16_t maxBitrate = 0;
        std::uint16_t maxBitrateCalcWindow = 0;

        std::uint8_t constantFrmRateIdc = 0;
        std::uint16_t avgFrmRate;
        
        std::uint32_t numDirectlyDependentViews = 0;
        std::vector<std::uint32_t> directlyDependentViewId;
        
        std::uint32_t viewDependencyInfoSrcOpId = 0;

        std::uint32_t numSeqParameterSets = 0;
        std::vector<std::uint32_t> seqParameterSetIdDelta;

        std::uint32_t numSubsetSeqParameterSets = 0;
        std::vector<std::uint32_t> subsetSeqParameterSetIdDelta;
        
        std::uint32_t numPicParameterSetMinus1 = 0;
        std::vector<std::uint32_t> picParameterSetIdDelta;

        std::uint32_t parameterSetsInfoSrcOpId = 0;
        bool motionVectorsOverPicBoundariesFlag = false;
        std::uint32_t maxBytesPerPicDenom = 0;
        std::uint32_t maxBitsPerMbDenom = 0;
        std::uint32_t log2MaxMvLengthHorizontal = 0;
        std::uint32_t log2MaxMvLengthVertical = 0;
        std::uint32_t maxNumReorderFrames = 0;
        std::uint32_t maxDecFrameBuffering = 0;

        OperationPoint() = default;
        explicit OperationPoint(BitstreamReader& reader)
        {
            operationPointId = reader.readExpoGlomb();
            priorityId = reader.readBits<std::uint8_t, 5>();
            temporalId = reader.readBits<std::uint8_t, 3>();
            numTargetOutputViewsMinus1 = reader.readExpoGlomb();
            for (auto j = 0; j <= numTargetOutputViewsMinus1; j++)
            {
                viewId.emplace_back(reader.readExpoGlomb());
            }
            profileLevelInfoPresentFlag = reader.readBits<bool, 1>();
            bitrateInfoPresentFlag = reader.readBits<bool, 1>();
            frmRateInfoPresentFlag = reader.readBits<bool, 1>();
            if (!numTargetOutputViewsMinus1)
            {
                viewDependencyInfoPresentFlag = reader.readBits<bool, 1>();
            }
            parameterSetsInfoPresentFlag = reader.readBits<bool, 1>();
            bitstreamRestrictionInfoPresentFlag = reader.readBits<bool, 1>();
            if (profileLevelInfoPresentFlag)
            {
                opProfileLevelIdc = reader.readBits<std::uint32_t, 24>();
            }
            if (bitrateInfoPresentFlag)
            {
                avgBitrate = reader.readBits<std::uint16_t, 16>();
                maxBitrate = reader.readBits<std::uint16_t, 16>();
                maxBitrateCalcWindow = reader.readBits<std::uint16_t, 16>();
            }
            if (frmRateInfoPresentFlag)
            {
                constantFrmRateIdc = reader.readBits<std::uint8_t, 2>();
                avgFrmRate = reader.readBits<std::uint16_t, 16>();
            }
            if (viewDependencyInfoPresentFlag)
            {
                numDirectlyDependentViews = reader.readExpoGlomb();
                for (auto j = 0; j < numDirectlyDependentViews; j++)
                {
                    directlyDependentViewId.emplace_back(reader.readExpoGlomb());
                }
            }
            else
            {
                viewDependencyInfoSrcOpId = reader.readExpoGlomb();
            }
            if (parameterSetsInfoPresentFlag)
            {
                numSeqParameterSets = reader.readExpoGlomb();
                for (auto j = 0; j < numSeqParameterSets; j++)
                {
                    seqParameterSetIdDelta.emplace_back(reader.readExpoGlomb());
                }
                numSubsetSeqParameterSets = reader.readExpoGlomb();
                for (auto j = 0; j < numSubsetSeqParameterSets; j++)
                {
                    subsetSeqParameterSetIdDelta.emplace_back(reader.readExpoGlomb());
                }
                numPicParameterSetMinus1 = reader.readExpoGlomb();
                for (auto j = 0; j <= numPicParameterSetMinus1; j++)
                {
                    picParameterSetIdDelta.emplace_back(reader.readExpoGlomb());
                }
            }
            else
            {
                parameterSetsInfoSrcOpId = reader.readExpoGlomb();
            }
            if (bitstreamRestrictionInfoPresentFlag)
            {
                motionVectorsOverPicBoundariesFlag = reader.readBits<bool, 1>();
                maxBytesPerPicDenom = reader.readExpoGlomb();
                maxBitsPerMbDenom = reader.readExpoGlomb();
                log2MaxMvLengthHorizontal = reader.readExpoGlomb();
                log2MaxMvLengthVertical = reader.readExpoGlomb();
                maxNumReorderFrames = reader.readExpoGlomb();
                maxDecFrameBuffering = reader.readExpoGlomb();
            }
        }

    };
    std::uint32_t numOperationPointsMinus1 = 0;
    std::vector<OperationPoint> operationPoints;

    ViewScalabilityInfo() = default;
    explicit ViewScalabilityInfo(BitstreamReader& reader)
    {
        numOperationPointsMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= numOperationPointsMinus1; i++)
        {
            operationPoints.emplace_back(reader);
        }
    }
};

struct MultiviewSceneInfo
{
    std::uint32_t maxDisparity = 0;

    MultiviewSceneInfo() = default;
    explicit MultiviewSceneInfo(BitstreamReader& reader)
    {
        maxDisparity = reader.readExpoGlomb();
    }
};

struct MultiviewAcquisitionInfo
{
    struct ParamSet
    {
        RealValue focalLengthX;
        RealValue focalLengthY;
        RealValue principalPointX;
        RealValue principalPointY;
        RealValue skew;
    };

    struct ExtrinsicParam
    {
        RealValue rotation[3][3];
        RealValue translation[3];
    };

    std::uint32_t numViewsMinus1 = 0;
    bool intrinsicParamFlag = false;
    bool extrinsicParamFlag = false;

    bool intrinsicParamsEqual = false;
    std::uint32_t precFocalLength = 0;
    std::uint32_t precPrincipalPoint = 0;
    std::uint32_t precSkewFactor = 0;
    std::vector<ParamSet> paramSets;

    std::uint32_t precRotationParam = 0;
    std::uint32_t precTranslationParam = 0;
    std::vector<ExtrinsicParam> extrinsicParams;

};

struct NonRequiredViewComponent
{
    struct InfoEntry
    {
        std::uint32_t viewOrderIndex = 0;
        std::uint32_t numNonRequiredViewComponentsMinus1 = 0;
        std::vector<std::uint32_t> indexDeltaMinus1;

        InfoEntry() = default;
        explicit InfoEntry(BitstreamReader& reader)
        {
            viewOrderIndex = reader.readExpoGlomb();
            numNonRequiredViewComponentsMinus1 = reader.readExpoGlomb();
            for (auto j = 0; j <= numNonRequiredViewComponentsMinus1; j++)
            {
                indexDeltaMinus1.emplace_back(reader.readExpoGlomb());
            }
        }
    };
    std::uint32_t numInfoEntries = 0;
    std::vector<InfoEntry> infoEntries;

    NonRequiredViewComponent() = default;
    explicit NonRequiredViewComponent(BitstreamReader& reader)
    {
        numInfoEntries = reader.readExpoGlomb();
        for (auto i = 0; i <= numInfoEntries; i++)
        {
            infoEntries.emplace_back(reader);
        }
    }
};

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

struct OperationPointNotPresent
{
    std::uint32_t numOperationPoints = 0;
    std::vector<std::uint32_t> operationPointNotPresentId;

    OperationPointNotPresent() = default;
    explicit OperationPointNotPresent(BitstreamReader& reader)
    {
        numOperationPoints = reader.readExpoGlomb();
        for (auto k = 0; k < numOperationPoints; k++)
        {
            operationPointNotPresentId.emplace_back(reader.readExpoGlomb());
        }
    }
};

struct OperationPointsNotPresent
{
    std::uint32_t numOperationPoints = 0;
    std::vector<std::uint32_t> operationPointNotPresentId;

    OperationPointsNotPresent() = default;
    explicit OperationPointsNotPresent(BitstreamReader& reader)
    {
        numOperationPoints = reader.readExpoGlomb();
        for (auto i = 0; i <= numOperationPoints; i++)
        {
            operationPointNotPresentId.emplace_back(reader.readExpoGlomb());
        }
    }
};

struct BaseViewTemporalHrd
{
    struct TemporalLayer
    {
        std::uint8_t seiMvcTemporalId = 0;
        bool seiMvcTimingInfoPresentFlag = false;
        std::uint32_t seiMvcNumUnitsInTick = 0;
        std::uint32_t seiMvcTimeScale = 0;
        bool seiMvcFixedFrameRateFlag = false;

        bool seiMvcNalHrdParametersPresentFlag = false;
        bool seiMvcVclHrdParametersPresentFlag = false;

        HrdParameters hrdParameters;
        bool seiMvcLowDelayHrdFlag = false;
        bool seiMvcPicStructPresentFlag = false;

        TemporalLayer() = default;
        explicit TemporalLayer(BitstreamReader& reader)
        {
            seiMvcTemporalId = reader.readBits<std::uint8_t, 3>();
            seiMvcTimingInfoPresentFlag = reader.readBits<bool, 1>();
            if (seiMvcTimingInfoPresentFlag)
            {
                seiMvcNumUnitsInTick = reader.readBits<std::uint32_t, 32>();
                seiMvcTimeScale = reader.readBits<std::uint32_t, 32>();
                seiMvcFixedFrameRateFlag = reader.readBits<bool, 1>();
            }
            seiMvcNalHrdParametersPresentFlag = reader.readBits<bool, 1>();
            if (seiMvcNalHrdParametersPresentFlag)
            {
                hrdParameters = HrdParameters{ reader };
            }
            seiMvcVclHrdParametersPresentFlag = reader.readBits<bool, 1>();
            if (seiMvcVclHrdParametersPresentFlag)
            {
                hrdParameters = HrdParameters{ reader };
            }
            if (seiMvcNalHrdParametersPresentFlag || seiMvcVclHrdParametersPresentFlag)
            {
                seiMvcLowDelayHrdFlag = reader.readBits<bool, 1>();
            }
            seiMvcPicStructPresentFlag = reader.readBits<bool, 1>();
        }
    };

    std::uint32_t numOfTemporalLayersInBaseViewMinus1 = 0;
    std::vector<TemporalLayer> temporalLayersInBaseView;

    BaseViewTemporalHrd() = default;
    explicit BaseViewTemporalHrd(BitstreamReader& reader)
    {
        numOfTemporalLayersInBaseViewMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= numOfTemporalLayersInBaseViewMinus1; i++)
        {
            temporalLayersInBaseView.emplace_back(reader);
        }
    }
};

struct MultiviewViewPosition
{
    std::uint32_t numViewsMinus1 = 0;
    std::vector<std::uint32_t> viewPosition;

    bool multiViewPositionExtensionFlag = false;

    MultiviewViewPosition() = default;
    explicit MultiviewViewPosition(BitstreamReader& reader)
    {
        numViewsMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= numViewsMinus1; i++)
        {
            viewPosition.emplace_back(reader.readExpoGlomb());
        }
        multiViewPositionExtensionFlag = reader.readBits<bool, 1>();
    }
};

struct MvcdScalableNesting
{
    struct ViewComponent
    {
        std::uint16_t seiViewId = 0;
        bool seiViewApplicablityFlag = false;

        ViewComponent() = default;
        explicit ViewComponent(BitstreamReader& reader)
        {
            seiViewId = reader.readBits<std::uint16_t, 10>();
            seiViewApplicablityFlag = reader.readBits<bool, 1>();
        }
    };

    struct ViewComponentOp
    {
        std::uint16_t seiOpViewId = 0;
        bool seiOpDepthFlag = false;
        bool seiOpTextureFlag = false;

        ViewComponentOp() = default;
        explicit ViewComponentOp(BitstreamReader& reader, bool opTextureFlag)
        {
            seiOpViewId = reader.readBits<std::uint16_t, 10>();
            if (!opTextureFlag)
            {
                seiOpDepthFlag = reader.readBits<bool, 1>();
                seiOpTextureFlag = reader.readBits<bool, 1>();
            }
            
        }
    };

    bool operationPointFlag = false;
    bool allViewComponentsInAuFlag = false;
    std::uint32_t numViewComponentsMinus1 = 0;
    std::vector<ViewComponent> viewComponents;

    bool seiOpTextureOnlyFlag = false;
    std::uint32_t numViewComponentsOpMinus1 = 0;
    std::vector<ViewComponentOp> viewComponentOps;

    std::uint8_t seiOpTemporalId = 0;

    std::uint8_t seiNestingZeroBit = 0;

    SEIMessage seiMessage;

    MvcdScalableNesting() = default;
    explicit MvcdScalableNesting(BitstreamReader& reader)
    {
        operationPointFlag = reader.readBits<bool, 1>();
        if (!operationPointFlag)
        {
            allViewComponentsInAuFlag = reader.readBits<bool, 1>();
            if (!allViewComponentsInAuFlag)
            {
                numViewComponentsMinus1 = reader.readExpoGlomb();
                for (auto i = 0; i <= numViewComponentsMinus1; i++)
                {
                    viewComponents.emplace_back(reader);
                }
            }
        }
        else
        {
            seiOpTextureOnlyFlag = reader.readBits<bool, 1>();
            numViewComponentsMinus1 = reader.readExpoGlomb();
            for (auto i = 0; i <= numViewComponentsOpMinus1; i++)
            {
                viewComponentOps.emplace_back(reader);
            }
            seiOpTemporalId = reader.readBits<std::uint8_t, 3>();
        }

        while (!reader.byteAligned())
        {
            seiNestingZeroBit = reader.readBits<std::uint8_t, 1>();
        }

        // TODO: sei message
    }
};

struct DepthRepresentationSEIElement
{
    RealValue val;
    std::uint8_t mantissaLenMinus1 = 0;

    DepthRepresentationSEIElement() = default;
    DepthRepresentationSEIElement(BitstreamReader& reader)
    {
        val.sign = reader.readBits<std::uint8_t, 1>();
        val.exponent = reader.readBits<std::uint8_t, 7>();
        mantissaLenMinus1 = reader.readBits<std::uint8_t, 5>();
        val.mantissa = reader.readBits<std::uint8_t>(mantissaLenMinus1);
    }
};

struct DepthRepresentationInfo
{
    struct ViewInfo
    {
        std::uint32_t depthInfoViewId = 0;
        std::uint32_t zAxisReferenceIView = 0;
        std::uint32_t disparityReferenceView = 0;
        DepthRepresentationSEIElement zNear;
        DepthRepresentationSEIElement zFar;
        DepthRepresentationSEIElement dMin;
        DepthRepresentationSEIElement dMax;

        ViewInfo() = default;
        explicit ViewInfo(BitstreamReader& reader, bool zNearFlag, bool zFarFlag, bool dMinFlag, bool dMaxFlag, bool zAxisEqualFlag)
        {
            depthInfoViewId = reader.readExpoGlomb();
            if ((zNearFlag || zFarFlag) && (!zAxisEqualFlag))
            {
                zAxisReferenceIView = reader.readExpoGlomb();
            }
            if (dMinFlag || dMaxFlag)
            {
                disparityReferenceView = reader.readExpoGlomb();
            }
            if (zNearFlag)
            {
                zNear = DepthRepresentationSEIElement{ reader };
            }
            if (zFarFlag)
            {
                zFar = DepthRepresentationSEIElement{ reader };
            }
            if (dMinFlag)
            {
                dMin = DepthRepresentationSEIElement{ reader };
            }
            if (dMaxFlag)
            {
                dMax = DepthRepresentationSEIElement{ reader };
            }
        }
    };

    bool allViewsEqualFlag = false;
    std::uint32_t numViewsMinus1 = 0;

    bool zNearFlag = false;
    bool zFarFlag = false;

    bool zAxisEqualFlag = false;
    std::uint32_t commonZAxisReferenceView = 0;
    bool dMinFlag = false;
    bool dMaxFlag = false;

    std::uint32_t depthRepresentationType = 0;
    std::vector<ViewInfo> viewInfos;
    std::uint32_t depthNonlinearRepresentationNumMinus1 = 0;
    std::vector<std::uint32_t> depthNonlinearRepresentationModel;

    DepthRepresentationInfo() = default;
    explicit DepthRepresentationInfo(BitstreamReader& reader)
    {
        allViewsEqualFlag = reader.readBits<bool, 1>();
        int numViews = 0;
        if (!allViewsEqualFlag)
        {
            numViewsMinus1 = reader.readExpoGlomb();
            numViews = numViewsMinus1 + 1;
        }
        else
        {
            numViews = 1;
        }
        zNearFlag = reader.readBits<bool, 1>();
        zFarFlag = reader.readBits<bool, 1>();
        if (zNearFlag || zFarFlag)
        {
            zAxisEqualFlag = reader.readBits<bool, 1>();
            if (zAxisEqualFlag)
            {
                commonZAxisReferenceView = reader.readExpoGlomb();
            }
        }
        dMinFlag = reader.readBits<bool, 1>();
        dMaxFlag = reader.readBits<bool, 1>();
        depthRepresentationType = reader.readExpoGlomb();
        for (auto i = 0; i < numViews; i++)
        {
            viewInfos.emplace_back(reader, zNearFlag, zFarFlag, dMinFlag, dMaxFlag, zAxisEqualFlag);
        }
        if (depthRepresentationType == 3)
        {
            depthNonlinearRepresentationNumMinus1 = reader.readExpoGlomb();
            depthNonlinearRepresentationModel.resize(depthNonlinearRepresentationNumMinus1 + 2);
            for (auto i = 1; i <= depthNonlinearRepresentationNumMinus1 + 1; i++)
            {
                depthNonlinearRepresentationModel[i] = reader.readExpoGlomb();
            }
        }
    }
};

struct ThreeDimensionalReferenceDisplayInfo
{
    struct RefDisplay
    {
        RealValue refBaseline;
        RealValue refDisplayWidth;
        RealValue refViewingDistance;
        bool additionalShitPresentFlag = false;
        std::uint16_t numSampleShiftPlus512 = 0;

        RefDisplay() = default;
        explicit RefDisplay(BitstreamReader& reader, bool refViewingDistanceFlag, int precRefDisplayWidth)
        {
            int v = 0;
            refBaseline.sign = 1;
            refBaseline.exponent = reader.readBits<std::uint8_t, 6>();
            if (refBaseline.exponent == 0)
            {
                v = std::max(0, precRefDisplayWidth - 30);
            }
            else if (0 < refBaseline.exponent && refBaseline.exponent < 63)
            {
                v = std::max(0, refBaseline.exponent + precRefDisplayWidth - 31);
            }
            else
            {
                v = 0;
            }
            refBaseline.mantissa = reader.readBits<std::uint8_t>(v);

            refDisplayWidth.sign = 1;
            refDisplayWidth.exponent = reader.readBits<std::uint8_t, 8>();

            if (refDisplayWidth.exponent == 0)
            {
                v = std::max(0, precRefDisplayWidth - 30);
            }
            else if (0 < refDisplayWidth.exponent && refDisplayWidth.exponent < 63)
            {
                v = std::max(0, refDisplayWidth.exponent + precRefDisplayWidth - 31);
            }
            else
            {
                v = 0;
            }
            refDisplayWidth.mantissa = reader.readBits<std::uint8_t>(v);
            if (refViewingDistanceFlag)
            {
                refViewingDistance.sign = 1;
                refViewingDistance.exponent = reader.readBits<std::uint8_t, 6>();
                if (refViewingDistance.exponent == 0)
                {
                    v = std::max(0, precRefDisplayWidth - 30);
                }
                else if (0 < refViewingDistance.exponent && refViewingDistance.exponent < 63)
                {
                    v = std::max(0, refViewingDistance.exponent + precRefDisplayWidth - 31);
                }
                else
                {
                    v = 0;
                }
                refViewingDistance.mantissa = reader.readBits<std::uint8_t>(v);
            }
            additionalShitPresentFlag = reader.readBits<bool, 1>();
            if (additionalShitPresentFlag)
            {
                numSampleShiftPlus512 = reader.readBits<std::uint16_t, 10>();
            }
        }
    };

    std::uint32_t precRefBaseline = 0;
    std::uint32_t precRefDisplayWidth = 0;
    bool refViewingDistanceFlag = false;
    std::uint32_t precRefViewingDist = 0;
    std::uint32_t numRefDisplaysMinus1 = 0;
    std::vector<RefDisplay> refDisplays;
    bool threeDimensionalReferenceDisplaysExtensionFlag = false;

    ThreeDimensionalReferenceDisplayInfo() = default;
    explicit ThreeDimensionalReferenceDisplayInfo(BitstreamReader& reader)
    {
        precRefBaseline = reader.readExpoGlomb();
        precRefDisplayWidth = reader.readExpoGlomb();
        refViewingDistanceFlag = reader.readBits<bool, 1>();

        if (refViewingDistanceFlag)
        {
            precRefViewingDist = reader.readExpoGlomb();
        }
        numRefDisplaysMinus1 = reader.readExpoGlomb();
        auto numRefDisplays = numRefDisplaysMinus1 + 1;
        for (auto i = 0; i < numRefDisplays; i++)
        {
            refDisplays.emplace_back(reader, refViewingDistanceFlag);
        }
    }
};

struct DepthTimingOffset
{
    std::uint8_t offsetLenMinus1 = 0;
    std::uint32_t depthDispDelayOffsetFp = 0;
    std::uint8_t depthDispDelayOffsetDp = 0;

    DepthTimingOffset() = default;
    explicit DepthTimingOffset(BitstreamReader& reader)
    {
        offsetLenMinus1 = reader.readBits<std::uint8_t, 5>();
        depthDispDelayOffsetFp = reader.readBits<std::uint32_t>(offsetLenMinus1 + 1);
        depthDispDelayOffsetDp = reader.readBits<std::uint8_t, 6>();
    }
};

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

constexpr auto SEIMessageTypes = std::make_tuple(
    std::declval<BufferingPeriod>(),
    std::declval<PicTiming>(),
    std::declval<PanScanRect>(),
    std::declval<FillerPayload>(),
    std::declval<UserDataRegisteredItuTT35>(),
    std::declval<UserDataUnregistered>(),
    std::declval<RecoveryPoint>(),
    std::declval<DecRefPicMarkingRepetition>(),
    std::declval<SparePic>(),
    std::declval<SceneInfo>(),
    std::declval<SubSeqInfo>(),
    std::declval<SubSeqLayerCharacteristics>(),
    std::declval<SubSeqCharacteristics>(),
    std::declval<FullFrameFreeze>(),
    std::declval<FullFrameFreezeRelease>(),
    std::declval<FullFrameSnapshot>(),
    std::declval<ProgressiveRefinementSegmentStart>(),
    std::declval<ProgressiveRefinementSegmentEnd>(),
    std::declval<MotionConstrainedSliceGroupSet>(),
    std::declval<FilmGrainCharacteristics>(),
    std::declval<DeblockingFilterDisplayPreference>(),
    std::declval<StereoVideoInfo>(),
    std::declval<PostFilterHint>(),
    std::declval<ToneMappingInfo>(),
    std::declval<ScalabilityInfo>(),
    std::declval<SubPicScalableLayer>(),
    std::declval<NonRequiredLayerRep>(),
    std::declval<PriorityLayerInfo>(),
    std::declval<LayersNotPresent>(),
    std::declval<LayerDependencyChange>(),
    std::declval<ScalableNesting>(),
    std::declval<BaseLayerTemporalHrd>(),
    std::declval<QualityLayerIntegrityCheck>(),
    std::declval<RedundantPicProperty>(),
    std::declval<Tl0DepRepIndex>(),
    std::declval<TlSwitchingPoint>(),
    std::declval<ParallelDecodingInfo>(),
    std::declval<MvcScalableNesting>(),
    std::declval<ViewScalabilityInfo>(),
    std::declval<MultiviewSceneInfo>(),
    std::declval<MultiviewAcquisitionInfo>(),
    std::declval<NonRequiredViewComponent>(),
    std::declval<ViewDependencyChange>(),
    std::declval<OperationPointsNotPresent>(),
    std::declval<BaseViewTemporalHrd>(),
    std::declval<FramePackingArrangement>(),
    std::declval<MultiviewViewPosition>(),
    std::declval<DisplayOrientation>(),
    std::declval<MvcdScalableNesting>(),
    std::declval<MvcdViewScalabilityInfo>(),
    std::declval<DepthRepresentationInfo>(),
    std::declval<ThreeDimensionalReferenceDisplaysInfo>(),
    std::declval<DepthTiming>(),
    std::declval<DepthSamplingInfo>(),
    std::declval<ConstrainedDepthParameterSetIdentifier>(),
    std::declval<MasteringDisplayColourVolume>(),
    std::declval<ReservedSEIMessage>());



struct SEIMessage
{
    std::vector<Byte> ffBytes;

    std::uint8_t lastPayloadTypeByte = 0;
    std::vector<Byte> ffBytes2;

    std::uint8_t lastPayloadSizeByte = 0;
    std::shared_ptr<std::uint8_t> seiPayload;

    SEIType seiPayloadType;

    SEIMessage() = default;
    explicit SEIMessage(DecodingContext& context, BitstreamReader& reader)
    {
        auto payloadType = 0;
        while (reader.nextBits<std::uint8_t, 8>() == 0xFF)
        {
            ffBytes.emplace_back(reader.readBits<std::uint8_t, 8>());
            payloadType += 255;
        }
        lastPayloadTypeByte = reader.readBits<std::uint8_t, 8>();
        payloadType += lastPayloadTypeByte;
        auto payloadSize = 0;
        while (reader.nextBits<std::uint8_t, 8>() == 0xFF)
        {
            ffBytes2.emplace_back(reader.readBits<std::uint8_t, 8>());
            payloadSize += 255;
        }
        lastPayloadSizeByte = reader.readBits<std::uint8_t, 8>();
        payloadSize += lastPayloadSizeByte;

        seiPayloadType = static_cast<SEIType>(payloadType);
        switch (seiPayloadType)
        {
        case SEIType::BufferingPeriod:
            readSEI<BufferingPeriod>(context, reader, payloadSize);
            break;
        case SEIType::PicTiming:
            readSEI<PicTiming>(context, reader, payloadSize);
            break;
        }

    }

    template<typename T>
    void readSEI(DecodingContext& context, BitstreamReader& reader, int size)
    {
        seiPayload = std::shared_ptr<std::uint8_t>(reinterpret_cast<std::uint8_t*>(new T(context, reader, size)), [](std::uint8_t* ptr)
            {
                auto obj = reinterpret_cast<T*>(ptr);
                delete obj;
            });
    }
};


