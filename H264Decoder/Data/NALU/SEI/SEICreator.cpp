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
#include <Utils/AutoInjector.h>

namespace SEITypeMapping
{
    constexpr auto NumberProbe = 10;

    template<SEIType EnumVal, typename T>
    using SEICreator = AutoInjector::ObjectCreator<10, SEIType, EnumVal, T, DecodingContext&, BitstreamReader&, int, NALUnit&>;

    using Mapping = AutoInjector::TypePack<
        SEICreator<SEIType::BufferingPeriod, BufferingPeriod>,
        SEICreator<SEIType::PicTiming, PicTiming>,
        SEICreator<SEIType::PanScanRect, PanScanRect>,
        SEICreator<SEIType::FillerPayload, FillerPayload>,
        SEICreator<SEIType::UserDataRegisteredItuTT35, UserDataRegisteredItuTT35>,
        SEICreator<SEIType::UserDataUnregistered, UserDataUnregistered>,
        SEICreator<SEIType::RecoveryPoint, RecoveryPoint>,
        SEICreator<SEIType::DecRefPicMarkingRepetition, DecRefPicMarkingRepetition>,
        SEICreator<SEIType::SparePic, SparePic>,
        SEICreator<SEIType::SceneInfo, SceneInfo>,
        SEICreator<SEIType::SubSeqInfo, SubSeqInfo>,
        SEICreator<SEIType::SubSeqLayerCharacteristics, SubSeqLayerCharacteristics>,
        SEICreator<SEIType::SubSeqCharacteristics, SubSeqCharacteristics>,
        SEICreator<SEIType::FullFrameFreeze, FullFrameFreeze>,
        SEICreator<SEIType::FullFrameFreezeRelease, FullFrameFreezeRelease>,
        SEICreator<SEIType::FullFrameSnapshot, FullFrameSnapshot>,
        SEICreator<SEIType::ProgressiveRefinementSegmentStart, ProgressiveRefinementSegmentStart>,
        SEICreator<SEIType::ProgressiveRefinementSegmentEnd, ProgressiveRefinementSegmentEnd>,
        SEICreator<SEIType::MotionConstrainedSliceGroupSet, MotionConstrainedSliceGroupSet>,
        SEICreator<SEIType::FilmGrainCharacteristics, FilmGrainCharacteristics>,
        SEICreator<SEIType::DeblockingFilterDisplayPreference, DeblockingFilterDisplayPreference>,
        SEICreator<SEIType::StereoVideoInfo, StereoVideoInfo>,
        SEICreator<SEIType::PostFilterHint, PostFilterHint>,
        SEICreator<SEIType::ToneMappingInfo, ToneMappingInfo>,
        SEICreator<SEIType::ScalabilityInfo, ScalabilityInfo>,
        SEICreator<SEIType::SubPicScalableLayer, SubPicScalableLayer>,
        SEICreator<SEIType::NonRequiredLayerRep, NonRequiredLayerRep>,
        SEICreator<SEIType::PriorityLayerInfo, PriorityLayerInfo>,
        SEICreator<SEIType::LayersNotPresent, LayersNotPresent>,
        SEICreator<SEIType::LayerDependencyChange, LayerDependencyChange>,
        SEICreator<SEIType::ScalableNesting, ScalableNesting>,
        SEICreator<SEIType::BaseLayerTemporalHrd, BaseLayerTemporalHrd>,
        SEICreator<SEIType::QualityLayerIntegrityCheck, QualityLayerIntegrityCheck>,
        SEICreator<SEIType::RedundantPicProperty, RedundantPicProperty>,
        SEICreator<SEIType::Tl0DepRepIndex, Tl0DepRepIndex>,
        SEICreator<SEIType::TlSwitchingPoint, TlSwitchingPoint>,
        SEICreator<SEIType::ParallelDecodingInfo, ParallelDecodingInfo>,
        SEICreator<SEIType::MvcScalableNesting, MvcScalableNesting>,
        SEICreator<SEIType::ViewScalabilityInfo, ViewScalabilityInfo>,
        SEICreator<SEIType::MultiviewSceneInfo, MultiviewSceneInfo>,
        SEICreator<SEIType::MultiviewAcquisitionInfo, MultiviewAcquisitionInfo>,
        SEICreator<SEIType::NonRequiredViewComponent, NonRequiredViewComponent>,
        SEICreator<SEIType::ViewDependencyChange, ViewDependencyChange>,
        SEICreator<SEIType::OperationPointsNotPresent, OperationPointsNotPresent>,
        SEICreator<SEIType::BaseViewTemporalHrd, BaseViewTemporalHrd>,
        SEICreator<SEIType::FramePackingArrangement, FramePackingArrangement>,
        SEICreator<SEIType::MultiviewViewPosition, MultiviewViewPosition>,
        SEICreator<SEIType::DisplayOrientation, DisplayOrientation>,
        SEICreator<SEIType::MvcdScalableNesting, MvcdScalableNesting>,
        SEICreator<SEIType::MvcdViewScalabilityInfo, MvcdViewScalabilityInfo>,
        SEICreator<SEIType::DepthRepresentationInfo, DepthRepresentationInfo>,
        SEICreator<SEIType::ThreeDimensionalReferenceDisplaysInfo, ThreeDimensionalReferenceDisplaysInfo>,
        SEICreator<SEIType::DepthTiming, DepthTiming>,
        SEICreator<SEIType::DepthSamplingInfo, DepthSamplingInfo>,
        SEICreator<SEIType::ConstrainedDepthParameterSetIdentifier, ConstrainedDepthParameterSetIdentifier>,
        //SEICreator<SEIType::GreenMetadata, GreenMetadata>,
        SEICreator<SEIType::MasteringDisplayColourVolume, MasteringDisplayColourVolume>,
        SEICreator<SEIType::ColourRemappingInfo, ColourRemappingInfo>,
        SEICreator<SEIType::ContentLightLevelInfo, ContentLightLevelInfo>,
        SEICreator<SEIType::AlternativeTransferCharacteristics, AlternativeTransferCharacteristics>,
        SEICreator<SEIType::AmbientViewingEnvironment, AmbientViewingEnvironment>,
        SEICreator<SEIType::ContentColourVolume, ContentColourVolume>,
        SEICreator<SEIType::EquirectangularProjection, EquirectangularProjection>,
        SEICreator<SEIType::CubemapProjection, CubemapProjection>,
        SEICreator<SEIType::SphereRotation, SphereRotation>,
        SEICreator<SEIType::RegionwisePacking, RegionwisePacking>,
        SEICreator<SEIType::OmniViewport, OmniViewport>,
        SEICreator<SEIType::AlternativeDepthInfo, AlternativeDepthInfo>,
        SEICreator<SEIType::SEIManifest, SEIManifest>,
        SEICreator<SEIType::SEIPrefixIndication, SEIPrefixIndication>,
        SEICreator<SEIType::ReservedSEIMessage, ReservedSEIMessage>
    > ;
}

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
