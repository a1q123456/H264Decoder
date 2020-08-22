#include "pch.h"
#include "SEICreator.h"
#include <Data/DecodingContext.h>
#include <IO/BitstreamReader.h>

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
#include <Data\NALU\SEI\AlternativeDepthInfo.h>
#include <Data\NALU\SEI\ColourRemappingInfo.h>
#include <Data\NALU\SEI\ContentLightLevelInfo.h>
#include <Data\NALU\SEI\SEIPrefixIndication.h>
#include <Data\NALU\SEI\SEIManifest.h>
#include <Data\NALU\SEI\OmniViewport.h>
#include <Data\NALU\SEI\RegionwisePacking.h>
#include <Data\NALU\SEI\SphereRotation.h>
#include <Data\NALU\SEI\CubemapProjection.h>
#include <Data\NALU\SEI\EquirectangularProjection.h>
#include <Data\NALU\SEI\ContentColourVolume.h>
#include <Data\NALU\SEI\AmbientViewingEnvironment.h>
#include <Data\NALU\SEI\AlternativeTransferCharacteristics.h>

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
            if constexpr (sizeof...(TCreator) != 0)
            {
                RegisterTypesImpl<Map, TCreator...>(std::forward<Map>(map));
            }
            
        }
    public:
        template<typename Map>
        static inline void RegisterTypes(Map&& map)
        {
            RegisterTypesImpl<Map, T...>(std::forward<Map>(map));
        }

    };

    template<typename SrcType, typename ...T>
    struct Injector
    {
    private:
        std::tuple<T...> tup;
    public:
        Injector() = delete;

        template<typename ...Args>
        explicit Injector(Args&&... args) : tup(args...)
        {

        }

        template<typename InjectTo, typename = std::enable_if_t<!std::is_convertible_v<SrcType, InjectTo>>>
        operator InjectTo() const
        {
            return std::get<InjectTo>(tup);
        }

        template<typename InjectTo, typename = std::enable_if_t<!std::is_convertible_v<SrcType, InjectTo>>>
        constexpr operator InjectTo&() &
        {
            return std::get<InjectTo&>(tup);
        }
    };

    template<typename SrcType, typename ...T>
    constexpr auto makeInjector(T&&... args)
    {
        return Injector<SrcType, T...>(args...);
    }


    template<size_t N, typename TSrc>
    struct PlaceHolder
    {
        template<typename T, typename = std::enable_if_t<!std::is_convertible_v<TSrc, T>>>
        constexpr operator T() const
        {
            return std::declval<T>();
        }

        template<typename T, typename = std::enable_if_t<!std::is_convertible_v<TSrc, T>>>
        constexpr operator T& ()&
        {
            return std::declval<T&>();
        }
    };

    template<typename T, typename BoolType, size_t Num, size_t I, size_t ...N>
    struct NumberParamsToConstructImpl
    {
        static constexpr size_t Val = NumberParamsToConstructImpl<T, typename std::is_constructible<T, PlaceHolder<N, T>&...>::type, Num - 1, N...>::Val;
    };

    template<typename T, typename BoolType>
    struct DefaultConstructibleChecker
    {
        static constexpr size_t Val = 0;
    };

    template<typename T>
    struct DefaultConstructibleChecker<T, std::true_type>
    {
        static constexpr size_t Val = 0;
    };

    template<typename T>
    struct DefaultConstructibleChecker<T, std::false_type>
    {
        static constexpr size_t Val = 999;
    };

    template<typename T, size_t Num, size_t I>
    struct NumberParamsToConstructImpl<T, std::false_type, Num, I>
    {
        static constexpr size_t Val = DefaultConstructibleChecker<T, typename std::is_default_constructible<T>::type>::Val;
    };

    template<typename T, size_t Num, size_t I>
    struct NumberParamsToConstructImpl<T, std::true_type, Num, I>
    {
        static constexpr size_t Val = Num;
    };

    template<typename T, size_t Num, size_t I, size_t ...N>
    struct NumberParamsToConstructImpl<T, std::true_type, Num, I, N...>
    {
        static constexpr size_t Val = Num;
    };

    template<typename T, size_t Cur, size_t I, size_t ...N>
    constexpr auto numberParamsToConstructImpl(std::index_sequence<I, N...>)
    {
        return NumberParamsToConstructImpl<T, typename std::is_constructible<T, PlaceHolder<N, T>&...>::type, Cur, I, N...>::Val;
    };

    template<typename T, size_t Cur>
    constexpr auto numberParamsToConstruct()
    {
        return numberParamsToConstructImpl<T, Cur>(std::make_index_sequence<Cur>{});
    };

    template<typename T, typename TInjector, size_t ...N>
    T* createSEIPtr(TInjector&& injector, std::index_sequence<N...>)
    {
        return new T((N, injector)...);
    }

    template<SEIType type, typename T>
    struct SEIMessageCreator
    {
        static constexpr SEIType seiType = type;

        std::shared_ptr<std::uint8_t> operator()(DecodingContext& context, BitstreamReader& reader, int payloadSize, NALUnit& nalu)
        {
            constexpr auto nParams = SEITypeMapping::numberParamsToConstruct<T, 10>();
            static_assert(nParams <= 10, "not constructible");
            std::make_index_sequence<nParams> indeies;
            auto injector = makeInjector<T>(context, reader, payloadSize, nalu);
            return std::shared_ptr<std::uint8_t>(reinterpret_cast<std::uint8_t*>(createSEIPtr<T>(injector, indeies)), [](std::uint8_t* ptr)
                {
                    auto obj = reinterpret_cast<T*>(ptr);
                    delete obj;
                });
        }
    };

    using Mapping = TypePack <SEIType::ConstrainedDepthParameterSetIdentifier,
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
        SEIMessageCreator<SEIType::MasteringDisplayColourVolume, MasteringDisplayColourVolume>,
        SEIMessageCreator<SEIType::ColourRemappingInfo, ColourRemappingInfo>,
        SEIMessageCreator<SEIType::ContentLightLevelInfo, ContentLightLevelInfo>,
        SEIMessageCreator<SEIType::AlternativeTransferCharacteristics, AlternativeTransferCharacteristics>,
        SEIMessageCreator<SEIType::AmbientViewingEnvironment, AmbientViewingEnvironment>,
        SEIMessageCreator<SEIType::ContentColourVolume, ContentColourVolume>,
        SEIMessageCreator<SEIType::EquirectangularProjection, EquirectangularProjection>,
        //SEIMessageCreator<SEIType::CubemapProjection, CubemapProjection>,
        SEIMessageCreator<SEIType::SphereRotation, SphereRotation>,
        SEIMessageCreator<SEIType::RegionwisePacking, RegionwisePacking>,
        SEIMessageCreator<SEIType::OmniViewport, OmniViewport>,
        SEIMessageCreator<SEIType::AlternativeDepthInfo, AlternativeDepthInfo>,
        SEIMessageCreator<SEIType::SEIManifest, SEIManifest>,
        SEIMessageCreator<SEIType::SEIPrefixIndication, SEIPrefixIndication>,
        SEIMessageCreator<SEIType::ReservedSEIMessage, ReservedSEIMessage>
    > ;
}

struct CCCC
{
    template<typename T>
    constexpr operator T() const
    {
        return std::declval<T>();
    }

    template<typename T>
    constexpr operator T& ()&
    {
        return std::declval<T>();
    }
    
};

struct SEIMap
{
    SEICreatorMap map;

    SEIMap()
    {
        using namespace SEITypeMapping;

        Mapping::RegisterTypes(map);
    }
};
SEIMap seiMap;

const SEICreatorMap& getSEICreator()
{
    static SEIMap seiMap;
    return seiMap.map;
}
