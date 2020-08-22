#pragma once
#include <IO/BitstreamReader.h>

struct DecodingContext;

struct BufferingPeriod
{
    struct Data
    {
        std::uint8_t initialCpbRemovalDelay = 0;
        std::uint8_t initialCpbRemovalDelayOffset = 0;

    };
    std::uint16_t spsId = 0;
    std::vector<Data> nalHrdBpData;
    std::vector<Data> vclHrdBpData;

    BufferingPeriod() = default;
    BufferingPeriod(DecodingContext& context, BitstreamReader& reader, int payloadSize);

};


