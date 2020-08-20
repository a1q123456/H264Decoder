#pragma once
#include <IO/BitstreamReader.h>

struct DepthRepresentationSEIElement
{
    DecimalValue val;
    std::uint8_t mantissaLenMinus1 = 0;

    DepthRepresentationSEIElement() = default;
    DepthRepresentationSEIElement(BitstreamReader& reader)
    {
        val.sign = reader.readBits<std::uint8_t, 1>();
        val.exponent = reader.readBits<std::uint8_t, 7>();
        mantissaLenMinus1 = reader.readBits<std::uint8_t, 5>();
        val.mantissa = reader.readBits<std::uint32_t>(mantissaLenMinus1);
    }
};


