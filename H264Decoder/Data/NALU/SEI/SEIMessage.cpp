#include "pch.h"
#include "SEIMessage.h"
#include "SEICreator.h"
#include <Data\NALUnit.h>

SEIMessage::SEIMessage(DecodingContext& context, BitstreamReader& reader, NALUnit& nal)
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
    seiPayload = getSEICreator().at(seiPayloadType)(context, reader, payloadSize, nal);

}
