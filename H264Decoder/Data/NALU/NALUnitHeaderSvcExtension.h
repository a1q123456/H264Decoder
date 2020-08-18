#pragma once

#include <IO/BitstreamReader.h>

struct NALUnitHeaderSvcExtension
{
    bool IDRFlag = false;
    std::uint8_t priorityId = 0;
    bool NoInterLayerPredFlag = false;
    std::uint8_t dependencyId = 0;
    std::uint8_t qualityId = 0;
    std::uint8_t temporalId = 0;
    bool useRefBasePicFlag = false;
    bool discardableFlag = false;
    bool outputFlag = false;
    std::uint8_t reservedThree2Bits = 0;

    NALUnitHeaderSvcExtension() = default;
    explicit NALUnitHeaderSvcExtension(BitstreamReader& reader)
    {
        IDRFlag = reader.readBits<std::uint8_t, 1>();
        priorityId = reader.readBits<std::uint8_t, 6>();
        NoInterLayerPredFlag = reader.readBits<std::uint8_t, 1>();
        dependencyId = reader.readBits<std::uint8_t, 3>();
        qualityId = reader.readBits<std::uint8_t, 4>();
        temporalId = reader.readBits<std::uint8_t, 3>();
        useRefBasePicFlag = reader.readBits<std::uint8_t, 1>();
        discardableFlag = reader.readBits<std::uint8_t, 1>();
        outputFlag = reader.readBits<std::uint8_t, 1>();
        reservedThree2Bits = reader.readBits<std::uint8_t, 2>();
    }
};

