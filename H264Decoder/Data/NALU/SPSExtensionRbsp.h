#pragma once
#include <IO/BitstreamReader.h>


struct SPSExtensionRbsp
{
    std::uint16_t spsId = 0;
    std::uint16_t auxFormatIdc = 0;

    bool bitDepthAuxMinus8 = false;
    bool alphaIncrFlag = false;
    std::uint32_t alphaOpaqueValue = 0;
    std::uint32_t alphaTransparentValue = 0;

    bool additionalExtensionFlag = false;

    RbspTrailingBits rbspTrailingBits;

    SPSExtensionRbsp() = default;
    explicit SPSExtensionRbsp(BitstreamReader& reader)
    {
        spsId = reader.readExpoGlomb();
        auxFormatIdc = reader.readExpoGlomb();
        if (auxFormatIdc != 0)
        {
            bitDepthAuxMinus8 = reader.readExpoGlomb();
            alphaIncrFlag = reader.readBits<bool, 1>();
            alphaOpaqueValue = reader.readBits<std::uint32_t>(bitDepthAuxMinus8 + 9);
            alphaTransparentValue = reader.readBits<std::uint32_t>(bitDepthAuxMinus8 + 9);
        }
        additionalExtensionFlag = reader.readBits<bool, 1>();
        rbspTrailingBits = RbspTrailingBits{ reader };
    }
};


