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
#include <Data\DecimalValue.h>

namespace SEITypeMapping
{
    template<SEIType Last, typename ...T>
    struct TypePack 
    {
    private:
        template<typename Map, typename CurT, typename ...TCreator>
        static inline void RegisterTypesImpl(Map&& map)
        {
            map[CurT::seiType] = CurT{};
            RegisterTypesImpl<Map, TCreator...>(std::forward<Map>(map));
        }
    public:
        template<typename Map>
        static inline void RegisterTypes(Map&& map)
        {
            RegisterTypesImpl<Map, T...>(std::forward<Map>(map));
        }

    };

    template<typename ...T>
    struct Injector
    {
    private:
        constexpr std::tuple<T...> tup;
    public:

        template<typename ...Args>
        constexpr explicit Injector(Args&&... args) : tup(std::make_tuple(args...))
        {

        }

        template<typename InjectTo>
        constexpr operator InjectTo() const
        {
            return std::get<InjectTo>(tup);
        }
    };

    template<typename ...T>
    constexpr auto makeInjector(T&&... args)
    {
        return Injector<T...>(args...);
    }
    
    template<size_t N, typename TSrc>
    struct PlaceHolder
    {
        template<typename T, typename = std::enable_if_t<!std::is_same_v<TSrc, T>>>
        operator T() const
        {
            return std::declval<T>();
        }
    };

    template<typename T, size_t All, size_t C, size_t ...N>
    constexpr auto numberParamsToConstructImpl(std::index_sequence<C, N...>)
    {
        if constexpr (std::is_constructible_v<T, PlaceHolder<N, T>...>)
        {
            return All;
        }
        return numberParamsToConstructImpl<T, All - 1>(std::make_index_sequence<All - 1>{});
    };

    template<typename T, size_t N>
    constexpr auto numberParamsToConstruct()
    {
        return numberParamsToConstructImpl<T>(std::make_index_sequence<N>{});
    };

    template<SEIType type, typename T>
    struct SEIMessageCreator
    {
        static constexpr SEIType seiType = type;

        std::shared_ptr<std::uint8_t> operator()(DecodingContext& context, BitstreamReader& reader, int payloadSize, NALUnit& nalu)
        {
            return std::shared_ptr<std::uint8_t>(reinterpret_cast<std::uint8_t*>(new T(context, reader, size)), [](std::uint8_t* ptr)
                {
                    auto obj = reinterpret_cast<T*>(ptr);
                    delete obj;
                });
        }
    };

    using Mapping = TypePack<SEIType::ConstrainedDepthParameterSetIdentifier,
        SEIMessageCreator<SEIType::BufferingPeriod, BufferingPeriod>,
        SEIMessageCreator<SEIType::PicTiming, PicTiming>,
        SEIMessageCreator<SEIType::PanScanRect, PanScanRect>,
        SEIMessageCreator<SEIType::FillerPayload, FillerPayload>,
        SEIMessageCreator<SEIType::UserDataRegisteredItuTT35, UserDataRegisteredItuTT35>,
        SEIMessageCreator<SEIType::UserDataUnregistered, UserDataUnregistered>,
        SEIMessageCreator<SEIType::RecoveryPoint, RecoveryPoint>,
        SEIMessageCreator<SEIType::DecRefPicMarkingRepetition, DecRefPicMarkingRepetition>,
        SEIMessageCreator<SEIType::SparePic, SparePic>,
        SEIMessageCreator<SEIType::SceneInfo, SceneInfo>,
        SEIMessageCreator<SEIType::SubSeqInfo, SubSeqInfo>,
        SEIMessageCreator<SEIType::SubSeqLayerCharacteristics, SubSeqLayerCharacteristics>,
        SEIMessageCreator<SEIType::SubSeqCharacteristics, SubSeqCharacteristics>,
        SEIMessageCreator<SEIType::FullFrameFreeze, FullFrameFreeze>,
        SEIMessageCreator<SEIType::FullFrameFreezeRelease, FullFrameFreezeRelease>,
        SEIMessageCreator<SEIType::FullFrameSnapshot, FullFrameSnapshot>,
        SEIMessageCreator<SEIType::ProgressiveRefinementSegmentStart, ProgressiveRefinementSegmentStart>,
        SEIMessageCreator<SEIType::ProgressiveRefinementSegmentEnd, ProgressiveRefinementSegmentEnd>,
        SEIMessageCreator<SEIType::MotionConstrainedSliceGroupSet, MotionConstrainedSliceGroupSet>,
        SEIMessageCreator<SEIType::FilmGrainCharacteristics, FilmGrainCharacteristics>,
        SEIMessageCreator<SEIType::DeblockingFilterDisplayPreference, DeblockingFilterDisplayPreference>,
        SEIMessageCreator<SEIType::StereoVideoInfo, StereoVideoInfo>,
        SEIMessageCreator<SEIType::PostFilterHint, PostFilterHint>,
        SEIMessageCreator<SEIType::ToneMappingInfo, ToneMappingInfo>,
        SEIMessageCreator<SEIType::ScalabilityInfo, ScalabilityInfo>,
        SEIMessageCreator<SEIType::SubPicScalableLayer, SubPicScalableLayer>,
        SEIMessageCreator<SEIType::NonRequiredLayerRep, NonRequiredLayerRep>,
        SEIMessageCreator<SEIType::PriorityLayerInfo, PriorityLayerInfo>,
        SEIMessageCreator<SEIType::LayersNotPresent, LayersNotPresent>,
        SEIMessageCreator<SEIType::LayerDependencyChange, LayerDependencyChange>,
        SEIMessageCreator<SEIType::ScalableNesting, ScalableNesting>,
        SEIMessageCreator<SEIType::BaseLayerTemporalHrd, BaseLayerTemporalHrd>,
        SEIMessageCreator<SEIType::QualityLayerIntegrityCheck, QualityLayerIntegrityCheck>,
        SEIMessageCreator<SEIType::RedundantPicProperty, RedundantPicProperty>,
        SEIMessageCreator<SEIType::Tl0DepRepIndex, Tl0DepRepIndex>,
        SEIMessageCreator<SEIType::TlSwitchingPoint, TlSwitchingPoint>,
        SEIMessageCreator<SEIType::ParallelDecodingInfo, ParallelDecodingInfo>,
        SEIMessageCreator<SEIType::MvcScalableNesting, MvcScalableNesting>,
        SEIMessageCreator<SEIType::ViewScalabilityInfo, ViewScalabilityInfo>,
        SEIMessageCreator<SEIType::MultiviewSceneInfo, MultiviewSceneInfo>,
        SEIMessageCreator<SEIType::MultiviewAcquisitionInfo, MultiviewAcquisitionInfo>,
        SEIMessageCreator<SEIType::NonRequiredViewComponent, NonRequiredViewComponent>,
        SEIMessageCreator<SEIType::ViewDependencyChange, ViewDependencyChange>,
        SEIMessageCreator<SEIType::OperationPointsNotPresent, OperationPointsNotPresent>,
        SEIMessageCreator<SEIType::BaseViewTemporalHrd, BaseViewTemporalHrd>,
        SEIMessageCreator<SEIType::FramePackingArrangement, FramePackingArrangement>,
        SEIMessageCreator<SEIType::MultiviewViewPosition, MultiviewViewPosition>,
        SEIMessageCreator<SEIType::DisplayOrientation, DisplayOrientation>,
        SEIMessageCreator<SEIType::MvcdScalableNesting, MvcdScalableNesting>,
        SEIMessageCreator<SEIType::MvcdViewScalabilityInfo, MvcdViewScalabilityInfo>,
        SEIMessageCreator<SEIType::DepthRepresentationInfo, DepthRepresentationInfo>,
        SEIMessageCreator<SEIType::ThreeDimensionalReferenceDisplaysInfo, ThreeDimensionalReferenceDisplaysInfo>,
        SEIMessageCreator<SEIType::DepthTiming, DepthTiming>,
        SEIMessageCreator<SEIType::DepthSamplingInfo, DepthSamplingInfo>,
        SEIMessageCreator<SEIType::ConstrainedDepthParameterSetIdentifier, ConstrainedDepthParameterSetIdentifier>,
        //SEIMessageCreator<SEIType::GreenMetadata, GreenMetadata>,
        //SEIMessageCreator<SEIType::MasteringDisplayColourVolume, MasteringDisplayColourVolume>,
        //SEIMessageCreator<SEIType::ColourRemappingInfo, ColourRemappingInfo>,
        //SEIMessageCreator<SEIType::ContentLightLevelInfo, ContentLightLevelInfo>,
        //SEIMessageCreator<SEIType::AlternativeTransferCharacteristics, AlternativeTransferCharacteristics>,
        //SEIMessageCreator<SEIType::AmbientViewingEnvironment, AmbientViewingEnvironment>,
        //SEIMessageCreator<SEIType::ContentColourVolume, ContentColourVolume>,
        //SEIMessageCreator<SEIType::EquirectangularProjection, EquirectangularProjection>,
        //SEIMessageCreator<SEIType::CubemapProjection, CubemapProjection>,
        //SEIMessageCreator<SEIType::SphereRotation, SphereRotation>,
        //SEIMessageCreator<SEIType::RegionwisePacking, RegionwisePacking>,
        //SEIMessageCreator<SEIType::OmniViewport, OmniViewport>,
        //SEIMessageCreator<SEIType::AlternativeDepthInfo, AlternativeDepthInfo>,
        //SEIMessageCreator<SEIType::SEIManifest, SEIManifest>,
        //SEIMessageCreator<SEIType::SEIPrefixIndication, SEIPrefixIndication>,
        SEIMessageCreator<SEIType::ReservedSEIMessage, ReservedSEIMessage>
    >;

}

constexpr auto ttt(char a)
{
    return a;
}

struct TestType
{
    TestType(int, int){}
};

template<size_t N>
struct AAA
{
    constexpr AAA() {}
    constexpr operator int() const
    {
        return N;
    }
};

template<size_t I, size_t C, size_t ...N>
constexpr auto f(std::index_sequence<C, N...>)
{
    if constexpr (I == 3)
    {
        return I;
    }
    //return f<I - 1>(std::make_index_sequence<I - 1>{});
    return 0;
}

auto test()
{

    std::unordered_map<SEIType, std::function<std::shared_ptr<std::uint8_t>>> map;
    SEITypeMapping::Mapping::RegisterTypes(map);
    
    constexpr AAA<1> aaa;

    constexpr std::index_sequence<3, 2, 1> c{};
    constexpr auto c = SEITypeMapping::numberParamsToConstructImpl<TestType, 3>(c);

    constexpr auto c = f<3>(std::make_index_sequence<3>{});
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


