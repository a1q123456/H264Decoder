#include <pch.h>
#include <Data/Byte.h>
#include "NALUnitReader.h"
#include <Data/NALU/SPSRbsp.h>
#include <Data/NALU/PPSRbsp.h>
#include <Data/NALU/SEIRbsp.h>



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
    switch (out.nalUnitType)
    {
    case NaluTypes::SPS:
        readRbsp<SPSRbsp>(rbspReader, out);
        break;
    case NaluTypes::PPS:
        readRbsp<PPSRbsp>(rbspReader, out);
        break;
    case NaluTypes::SEI:
        readRbsp<SEIRbsp>(rbspReader, out);
    }

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
