#pragma once
#include <cstdint>
#include "BitstreamReader.h"
#include "ByteHelper.h"
#include <Data/NALUnit.h>
#include <Data/DecodingContext.h>

constexpr const int NALU_START_CODE_LEN = 3;

class NALUnitReader
{
public:
    explicit NALUnitReader(DecodingContext& context, ByteStream& bs, bool byteAligned);
    bool readNALUnit(NALUnit& out);
private:
    template<typename T>
    void readRbsp(BitstreamReader& rbspReader, NALUnit& out)
    {
        out.rbsp = std::shared_ptr<std::uint8_t>(reinterpret_cast<std::uint8_t*>(new T(context, rbspReader, out)), [](std::uint8_t* ptr)
            {
                auto obj = reinterpret_cast<T*>(ptr);
                delete obj;
            });
    }

    BitstreamReader readAnnexBNALPayload();

    void readNALUnitStartCode();
    std::uint8_t readNALUnitForbiddenZeroBit(BitstreamReader& br);
    std::uint8_t readNALRefIdc(BitstreamReader& br);
    std::uint8_t readNALUnitType(BitstreamReader& br);


private:

    DecodingContext& context;
    ByteStream& bs;
    BitstreamReader annexBReader;
    bool byteAligned = true;
};

