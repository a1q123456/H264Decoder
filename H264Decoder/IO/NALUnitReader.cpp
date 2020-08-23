#include <pch.h>
#include <Data/Byte.h>
#include "NALUnitReader.h"
#include <Utils/AutoInjector.h>
#include <Data/NALU/SPSRbsp.h>
#include <Data/NALU/PPSRbsp.h>
#include <Data/NALU/SEIRbsp.h>
#include <Data/NALU/DPSRbsp.h>
#include <Data/NALU/AUDRbsp.h>
#include <Data/NALU/EndOfSequenceRbsp.h>
#include <Data/NALU/EndOfStreamRbsp.h>
#include <Data/NALU/AUDRbsp.h>
#include <Data/NALU/AUDRbsp.h>
#include <Data/NALU/AUDRbsp.h>
#include <Data/NALU/AUDRbsp.h>
#include <Data/NALU/AUDRbsp.h>
#include <Data/NALU/AUDRbsp.h>
#include <Data/NALU/AUDRbsp.h>
#include <Data/NALU/AUDRbsp.h>
#include <Data/NALU/AUDRbsp.h>
#include <Data\NALU\FilterDataRbsp.h>
#include <Data\NALU\SPSExtensionRbsp.h>
#include <Data\NALU\SliceLayerExtensionRbsp.h>
#include <Data\NALU\FillerDataRbsp.h>

namespace NALUnitMapping
{
    constexpr auto NumberProbe = 10;

    template<NaluTypes EnumVal, typename T>
    using NALUCreator = AutoInjector::ObjectCreator<10, NaluTypes, EnumVal, T, DecodingContext&, BitstreamReader&, NALUnit&>;

    using Mapping = AutoInjector::TypePack<
        //NALUCreator<NaluTypes::CodedSliceNonIDRPicture, CodedSliceNonIDRPictureRbsp>,
        //NALUCreator<NaluTypes::CodedSliceDataPartitionA, CodedSliceDataPartitionARbsp>,
        //NALUCreator<NaluTypes::CodedSliceDataPartitionB, CodedSliceDataPartitionBRbsp>,
        //NALUCreator<NaluTypes::CodedSliceDataPartitionC, CodedSliceDataPartitionCRbsp>,
        //NALUCreator<NaluTypes::CodedSliceIDRPicture, CodedSliceIDRPictureRbsp>,
        NALUCreator<NaluTypes::SEI, SEIRbsp>,
        NALUCreator<NaluTypes::SPS, SPSRbsp>,
        NALUCreator<NaluTypes::PPS, PPSRbsp>,
        NALUCreator<NaluTypes::AUD, AUDRbsp>,
        NALUCreator<NaluTypes::EndOfSequence, EndOfSequenceRbsp>,
        NALUCreator<NaluTypes::EndOfStream, EndOfStreamRbsp>,
        NALUCreator<NaluTypes::FillerData, FillerDataRbsp>,
        NALUCreator<NaluTypes::SPSExtension, SPSExtensionRbsp>,
        //NALUCreator<NaluTypes::PrefixNALUnit, PrefixNALUnitRbsp>,
        NALUCreator<NaluTypes::SubsetSPS, SubsetSPSRbsp>,
        NALUCreator<NaluTypes::DPS, DPSRbsp>,
        //NALUCreator<NaluTypes::PictureWithoutPartiting, PictureWithoutPartitingRbsp>,
        NALUCreator<NaluTypes::SliceLayerExtension, SliceLayerExtensionRbsp>
        //NALUCreator<NaluTypes::DepthOrThreeDAVCSliceLayerExtension, DepthOrThreeDAVCSliceLayerExtensionRbsp>,
        //NALUCreator<NaluTypes::DepthOrTextureViewSliceLayerExtension, DepthOrTextureViewSliceLayerExtensionRbsp>
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

RbspCreator creator;

NALUnitReader::NALUnitReader(DecodingContext& context, ByteStream& bs, bool byteAligned) :
    bs(bs),
    context(context),
    annexBReader(bs),
    byteAligned(byteAligned)
{

}

bool NALUnitReader::readNALUnit(NALUnit& out)
{
    readNALUnitStartCode();

    auto nalUnit = readAnnexBNALPayload();

    out.forbiddenZeroBit = readNALUnitForbiddenZeroBit(nalUnit);
    out.nalRefIdc = readNALRefIdc(nalUnit);
    out.nalUnitType = static_cast<NaluTypes>(readNALUnitType(nalUnit));
    auto nalUnitHeaderBytes = 1;
    auto iNalUnitType = static_cast<int>(out.nalUnitType);
    if (iNalUnitType == 14 || iNalUnitType == 20 || iNalUnitType == 21)
    {
        if (iNalUnitType != 21)
        {
            out.svcExtensionFlag = nalUnit.readBits<std::uint8_t, 1>();
        }
        else
        {
            out.avc3DExtensionFlag = nalUnit.readBits<std::uint8_t, 1>();
        }
        if (out.svcExtensionFlag)
        {
            out.nalUnitHeaderSvcExtension = NALUnitHeaderSvcExtension{ nalUnit };
            nalUnitHeaderBytes += 3;
        }
        else if (out.avc3DExtensionFlag)
        {
            out.nalUnitHeader3DavcExtension = NALUnitHeader3DavcExtension{ nalUnit };
            nalUnitHeaderBytes += 2;
        }
        else
        {
            out.nalUnitHeaderMvcExtension = NALUnitHeaderMvcExtension{ nalUnit };
            nalUnitHeaderBytes += 3;
        }
    }


    std::size_t numBytesInRbsp = 0;
    auto numBytesInNALunit = nalUnit.totalSize();
    std::vector<Byte> rbsp;
    rbsp.resize(numBytesInNALunit);
    for (std::size_t i = nalUnitHeaderBytes; i < numBytesInNALunit; i++)
    {
        if (i + 2 < numBytesInNALunit && nalUnit.nextBits<std::uint32_t, 24>() == 0x000003)
        {
            rbsp[numBytesInRbsp++] = static_cast<Byte>(nalUnit.readBits<std::uint8_t, 8>());
            rbsp[numBytesInRbsp++] = static_cast<Byte>(nalUnit.readBits<std::uint8_t, 8>());
            i += 2;
            // discard the emulation_prevention_three_byte
            nalUnit.readBits<std::uint8_t, 8>();
        }
        else
        {
            rbsp[numBytesInRbsp++] = static_cast<Byte>(nalUnit.readBits<std::uint8_t, 8>());
        }
    }
    assert(numBytesInRbsp <= numBytesInNALunit);
    rbsp.resize(numBytesInRbsp);

    BitstreamReader rbspReader(std::move(rbsp));
    out.rbsp = creator.map.at(out.nalUnitType)(context, rbspReader, out);

    return out.forbiddenZeroBit == 0;
}

BitstreamReader NALUnitReader::readAnnexBNALPayload()
{
    std::vector<Byte> data;
    data.reserve(300);

    while (true)
    {

        auto next3Bytes = annexBReader.nextBits<std::uint32_t, 24>();
        if (next3Bytes == 0 || next3Bytes == 1)
        {
            break;
        }
        data.push_back(annexBReader.readBits<std::uint8_t, 8>());
    }
    return BitstreamReader(std::move(data));
}

void NALUnitReader::readNALUnitStartCode()
{
    // make decoder byte-aligned
    while (!byteAligned)
    {
        auto data = annexBReader.nextBits<std::uint32_t, 32>();
        if (data == 0x00000001)
        {
            annexBReader.advancePos(32);

            auto nextData = annexBReader.nextBits<std::uint32_t, 24>();
            if (nextData == 0x000003)
            {
                annexBReader.advancePos(3);
            }
            else if (nextData == 0x000001)
            {
                // a start code prefix, do nothing
            }
            else
            {
                // not aligned
                continue;
            }

            byteAligned = true;

            break;
        }
        else
        {
            annexBReader.advancePos(1);
        }
    }

    auto startCode = annexBReader.nextBits<std::uint32_t, 32>();
    if (startCode == 0x00000001)
    {
        annexBReader.advancePos(32);
        return;
    }
    else if ((startCode & 0xFFFFFF00) == 0x00000100)
    {
        annexBReader.advancePos(24);
        return;
    }
    else
    {
        annexBReader.advancePos(8);
    }

    readNALUnitStartCode();
}

std::uint8_t NALUnitReader::readNALUnitForbiddenZeroBit(BitstreamReader& br)
{
    return br.readBits<std::uint8_t, 1>();
}

std::uint8_t NALUnitReader::readNALRefIdc(BitstreamReader& br)
{
    return br.readBits<std::uint8_t, 2>();
}

std::uint8_t NALUnitReader::readNALUnitType(BitstreamReader& br)
{
    return br.readBits<std::uint8_t, 5>();
}
