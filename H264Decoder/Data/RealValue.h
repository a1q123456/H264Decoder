#pragma once


struct DecimalValue
{
    std::uint8_t sign = 0;

    std::uint8_t exponent = 0;
    std::uint32_t mantissa = 0;

    std::uint32_t fp = 0;
    std::uint8_t dp = 0;
};

int GetMantisaLength(int exponent, int prec)
{
    if (exponent == 0)
    {
        return std::max(0, prec - 30);
    }
    else
    {
        return std::max(0, exponent + prec - 31);
    }
}

