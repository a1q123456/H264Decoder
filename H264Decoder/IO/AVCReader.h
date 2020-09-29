#pragma once
#include <cstdint>
#include "BitstreamReader.h"
#include "ByteHelper.h"
#include <Data/NALUnit.h>
#include <Data/DecodingContext.h>

constexpr const int NALU_START_CODE_LEN = 3;

class AVCReader
{
public:
    explicit AVCReader(DecodingContext& context, ByteStream& bs, bool byteAligned);
    bool readNALUnit(NALUnit& out);
    const std::vector<NALUnit>& getSPS() const noexcept;
    const std::vector<NALUnit>& getSPSExt() const noexcept;
    const std::vector<NALUnit>& getPPS() const noexcept;
private:
    BitstreamReader readAVCPayload(std::uint32_t sz);

    std::uint32_t readNALUnitLength();
    std::uint8_t readNALUnitForbiddenZeroBit(BitstreamReader& br);
    std::uint8_t readNALRefIdc(BitstreamReader& br);
    std::uint8_t readNALUnitType(BitstreamReader& br);


private:

    DecodingContext& context;
    ByteStream& bs;
    BitstreamReader bsReader;
    std::vector<NALUnit> sps;
    std::vector<NALUnit> pps;
    std::vector<NALUnit> spsExt;
};

