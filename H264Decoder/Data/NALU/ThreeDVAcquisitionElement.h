#pragma once
#include <IO/BitstreamReader.h>

struct DecodingContext;

struct ThreeDVAcquisitionElement
{
    struct Value
    {
        std::uint8_t matissaLenMinus1 = 0;
        std::uint8_t prec = 0;
        bool sign0 = false;
        std::uint16_t exponent0 = 0;
        std::uint16_t mantissa0 = 0;

        bool skipFlag = false;
        bool sign1 = false;
        bool exponentSkipFlag = false;
        std::uint16_t exponent1 = 0;
        std::int16_t mantissaDiff;
    };

    bool elementEqualFlag = false;
    std::vector<Value> values;

    ThreeDVAcquisitionElement() = default;

    void FromBitstream(const DecodingContext& context, BitstreamReader& reader, int index, int numViews, int deltaFlag,
        int predDirection, int precMode, int expLen,
        std::vector<std::vector<std::int8_t>>& outSign,
        std::vector<std::vector<std::uint32_t>>& outExp,
        std::vector<std::vector<std::uint32_t>>& outMantissa,
        std::vector<std::vector<std::uint32_t>>& outManLen);
};

