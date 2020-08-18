#pragma once


struct RealValue
{
    std::uint8_t sign = 0;
    std::uint8_t exponent = 0;
    std::uint32_t mantissa = 0;

    double operator double()
    {
    }
};

