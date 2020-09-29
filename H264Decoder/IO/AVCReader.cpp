#include <pch.h>
#include <Data/Byte.h>
#include "AVCReader.h"
#include "NALUMapping.h"
#include <Data/NALU/NALUnitHeader3DavcExtension.h>
#include <Data/NALU/NALUnitHeaderSvcExtension.h>
#include <Data/NALU/NALUnitHeaderMvcExtension.h>


AVCReader::AVCReader(DecodingContext& context, ByteStream& bs, bool byteAligned) :
    bs(bs),
    context(context),
    bsReader(bs)
{
    auto version = bsReader.readBits<std::uint8_t, 8>();
    auto profile = bsReader.readBits<std::uint8_t, 8>();
    auto profileCompatbility = bsReader.readBits<std::uint8_t, 8>();
    auto level = bsReader.readBits<std::uint8_t, 8>();
    auto reserved = bsReader.readBits<std::uint8_t, 6>();
    auto lengthSizeMinusOne = bsReader.readBits<std::uint8_t, 2>();
    auto reserved2 = bsReader.readBits<std::uint8_t, 3>();
    auto numSps = bsReader.readBits<std::uint8_t, 5>();
    for (auto i = 0; i < numSps; i++)
    {
        NALUnit nalu;
        readNALUnit(nalu);
        sps.emplace_back(std::move(nalu));
    }

    auto numPps = bsReader.readBits<std::uint8_t, 8>();
    for (auto i = 0; i < numPps; i++)
    {
        NALUnit nalu;
        readNALUnit(nalu);
        pps.emplace_back(std::move(nalu));
    }
}

bool AVCReader::readNALUnit(NALUnit& out)
{
    try
    {
        auto len = readNALUnitLength();

        auto nalUnit = readAVCPayload(len);

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
        if (creator.map.find(out.nalUnitType) == std::end(creator.map))
        {
            return true;
        }
        out.rbsp = creator.map.at(out.nalUnitType)(context, rbspReader, out);

        return out.forbiddenZeroBit == 0;
    }
    catch (std::ios::failure)
    {
        return false;
    }
}

const std::vector<NALUnit>& AVCReader::getSPS() const noexcept
{
    return sps;
}

const std::vector<NALUnit>& AVCReader::getPPS() const noexcept
{
    return pps;
}

BitstreamReader AVCReader::readAVCPayload(std::uint32_t sz)
{
    std::vector<Byte> data;
    data.reserve(sz);

    while (sz > 0)
    {
        data.push_back(bsReader.readBits<std::uint8_t, 8>());
        sz--;
    }
    return BitstreamReader(std::move(data));
}

std::uint32_t AVCReader::readNALUnitLength()
{
    return bsReader.readBits<std::uint32_t, 16>();
}

std::uint8_t AVCReader::readNALUnitForbiddenZeroBit(BitstreamReader& br)
{
    return br.readBits<std::uint8_t, 1>();
}

std::uint8_t AVCReader::readNALRefIdc(BitstreamReader& br)
{
    return br.readBits<std::uint8_t, 2>();
}

std::uint8_t AVCReader::readNALUnitType(BitstreamReader& br)
{
    return br.readBits<std::uint8_t, 5>();
}
