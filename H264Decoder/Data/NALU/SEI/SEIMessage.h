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
            // sei message
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


