#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/SEI/SEIType.h>
#include <Data\NALUnit.h>

struct DecodingContext;

struct SEIMessage
{
    std::vector<Byte> ffBytes;

    std::uint8_t lastPayloadTypeByte = 0;
    std::vector<Byte> ffBytes2;

    std::uint8_t lastPayloadSizeByte = 0;
    std::shared_ptr<std::uint8_t> seiPayload;

    SEIType seiPayloadType;

    SEIMessage() = default;
    explicit SEIMessage(DecodingContext& context, BitstreamReader& reader, NALUnit& nal);

};


