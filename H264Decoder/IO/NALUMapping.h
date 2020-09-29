#pragma once

#include <Utils/AutoInjector.h>
#include <Data/NALU/SPSRbsp.h>
#include <Data/NALU/PPSRbsp.h>
#include <Data/NALU/SEIRbsp.h>
#include <Data/NALU/DPSRbsp.h>
#include <Data/NALU/AUDRbsp.h>
#include <Data/NALU/EndOfSequenceRbsp.h>
#include <Data/NALU/EndOfStreamRbsp.h>
#include <Data\NALU\FillerDataRbsp.h>
#include <Data\NALU\SPSExtensionRbsp.h>
#include <Data\NALU\FillerDataRbsp.h>

namespace NALUnitMapping
{
    constexpr auto NumberProbe = 10;

    template<NaluTypes EnumVal, typename T>
    using NALUCreator = AutoInjector::ObjectCreator<10, NaluTypes, EnumVal, T, DecodingContext&, BitstreamReader&, NALUnit&>;

    using Mapping = AutoInjector::TypePack<
        NALUCreator<NaluTypes::SEI, SEIRbsp>,
        NALUCreator<NaluTypes::SPS, SPSRbsp>,
        NALUCreator<NaluTypes::PPS, PPSRbsp>,
        NALUCreator<NaluTypes::AUD, AUDRbsp>,
        NALUCreator<NaluTypes::EndOfSequence, EndOfSequenceRbsp>,
        NALUCreator<NaluTypes::EndOfStream, EndOfStreamRbsp>,
        NALUCreator<NaluTypes::FillerData, FillerDataRbsp>,
        NALUCreator<NaluTypes::SPSExtension, SPSExtensionRbsp>,
        NALUCreator<NaluTypes::SubsetSPS, SubsetSPSRbsp>,
        NALUCreator<NaluTypes::DPS, DPSRbsp>
    >;
}

using RbspMap = std::unordered_map<NaluTypes, std::function<std::shared_ptr<std::uint8_t>(DecodingContext&, BitstreamReader&, NALUnit&)>>;


struct RbspCreator
{
    RbspMap map;

    RbspCreator()
    {
        using namespace NALUnitMapping;

        Mapping::RegisterTypes(map);
    }
};

inline RbspCreator creator;

