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

namespace SEITypeMapping
{
    template<size_t I, typename TCur, typename ...TArr>
    struct FindTypeArrayImpl
    {
        using Type = FindTypeArrayImpl<I - 1, TArr...>::Type;
    };

    template<typename TCur, typename ...TArr>
    struct FindTypeArrayImpl<0, TCur, TArr...>
    {
        using Type = TCur;
    };


    template<typename ...T>
    struct TypePack 
    {
    public:
        template<size_t I>
        struct FindTypeArray
        {
            using Type = FindTypeArrayImpl<I, T...>::Type;
        };
    };

    using Mapping = TypePack<BufferingPeriod,
        PicTiming,
        PanScanRect,
        FillerPayload,
        UserDataRegisteredItuTT35,
        UserDataUnregistered,
        RecoveryPoint,
        DecRefPicMarkingRepetition,
        SparePic,
        SceneInfo,
        SubSeqInfo,
        SubSeqLayerCharacteristics,
        SubSeqCharacteristics,
        FullFrameFreeze,
        FullFrameFreezeRelease,
        FullFrameSnapshot,
        ProgressiveRefinementSegmentStart,
        ProgressiveRefinementSegmentEnd,
        MotionConstrainedSliceGroupSet,
        FilmGrainCharacteristics,
        DeblockingFilterDisplayPreference,
        StereoVideoInfo,
        PostFilterHint,
        ToneMappingInfo,
        ScalabilityInfo,
        SubPicScalableLayer,
        NonRequiredLayerRep,
        PriorityLayerInfo,
        LayersNotPresent,
        LayerDependencyChange,
        ScalableNesting,
        BaseLayerTemporalHrd,
        QualityLayerIntegrityCheck,
        RedundantPicProperty,
        Tl0DepRepIndex,
        TlSwitchingPoint,
        ParallelDecodingInfo,
        MvcScalableNesting,
        ViewScalabilityInfo,
        MultiviewSceneInfo,
        MultiviewAcquisitionInfo,
        NonRequiredViewComponent,
        ViewDependencyChange,
        OperationPointsNotPresent,
        BaseViewTemporalHrd,
        FramePackingArrangement,
        MultiviewViewPosition,
        DisplayOrientation,
        MvcdScalableNesting,
        MvcdViewScalabilityInfo,
        DepthRepresentationInfo,
        ThreeDimensionalReferenceDisplaysInfo,
        DepthTiming,
        DepthSamplingInfo,
        ConstrainedDepthParameterSetIdentifier,
        MasteringDisplayColourVolume,
        ReservedSEIMessage>;
}


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


