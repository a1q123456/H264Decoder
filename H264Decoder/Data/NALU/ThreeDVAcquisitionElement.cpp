#include "pch.h"
#include "ThreeDVAcquisitionElement.h"
#include <Data/DecodingContext.h>

void ThreeDVAcquisitionElement::FromBitstream(const DecodingContext& context, BitstreamReader& reader, int index, int numViews, int deltaFlag, int predDirection, int precMode, int expLen, std::vector<std::vector<std::int8_t>>& outSign, std::vector<std::vector<std::uint32_t>>& outExp, std::vector<std::vector<std::uint32_t>>& outMantissa, std::vector<std::vector<std::uint32_t>>& outManLen)
{
    if (numViews - deltaFlag > 1)
    {
        elementEqualFlag = reader.readBits<std::uint8_t, 1>();
    }
    int numValues = 0;
    if (!elementEqualFlag)
    {
        numValues = numViews - deltaFlag;
    }
    else
    {
        numValues = 1;
    }
    int manLen = 0;

    for (auto i = 0; i < numValues; i++)
    {
        Value value;
        if (predDirection == 2 && i == 0)
        {
            if (precMode == 0)
            {
                auto matissaLenMinus1 = reader.readBits<std::uint8_t, 5>();
                value.matissaLenMinus1 = matissaLenMinus1;
                outManLen[index][i] = manLen = matissaLenMinus1 + 1;
            }
            else
            {
                auto prec = reader.readBits<std::uint8_t, 5>();
                value.prec = prec;
            }
        }
        if (predDirection == 2)
        {
            value.sign0 = reader.readBits<std::uint8_t, 1>();
            outSign[index][i] = value.sign0;
            value.exponent0 = reader.readBits<std::uint16_t>(expLen);
            outExp[index][i] = value.exponent0;
            if (precMode == 1)
            {
                if (value.exponent0 == 1)
                {
                    outManLen[index][i] = manLen = std::max(0, value.prec - 30);
                }
                else
                {
                    outManLen[index][i] = manLen = std::max(0, value.exponent0 + value.prec - 31);
                }
            }
            value.mantissa0 = reader.readBits<std::uint16_t>(manLen);
            outMantissa[index][i] = value.mantissa0;
        }
        else
        {
            value.skipFlag = reader.readBits<std::uint8_t, 1>();
            if (!value.skipFlag)
            {
                value.sign1 = reader.readBits<std::uint8_t, 1>();
                outSign[index][i] = value.sign1;
                value.exponentSkipFlag = reader.readBits<std::uint8_t, 1>();
                if (!value.exponentSkipFlag)
                {
                    value.exponent1 = reader.readBits<std::uint16_t>(expLen);
                    outExp[index][i] = value.exponent1;
                }
                else
                {
                    outExp[index][i] = outExp[context.currentDPS().dpsRbsp.refDpsId0][i];
                }
                value.mantissaDiff = reader.readSignedExpoGlomb();
                auto mantissaPred = ((outMantissa[context.currentDPS().dpsRbsp.refDpsId0][i] * context.currentDPS().dpsRbsp.predWeight0 +
                    outMantissa[context.currentDPS().dpsRbsp.refDpsId1][i] * (64 - context.currentDPS().dpsRbsp.predWeight0) + 32) >> 6);
                outMantissa[index][i] = mantissaPred + value.mantissaDiff;
                outManLen[index][i] = outManLen[context.currentDPS().dpsRbsp.refDpsId0][i];
            }
            else
            {
                outSign[index][i] = outSign[context.currentDPS().dpsRbsp.refDpsId0][i];
                outExp[index][i] = outExp[context.currentDPS().dpsRbsp.refDpsId0][i];
                outMantissa[index][i] = outMantissa[context.currentDPS().dpsRbsp.refDpsId0][i];
                outManLen[index][i] = outManLen[context.currentDPS().dpsRbsp.refDpsId0][i];
            }
        }
    }
    if (elementEqualFlag)
    {
        for (auto i = 1; i < numViews - deltaFlag; i++)
        {
            outSign[index][i] = outSign[index][0];
            outExp[index][i] = outExp[index][0];
            outMantissa[index][i] = outMantissa[index][0];
            outManLen[index][i] = outManLen[index][0];
        }
    }
}
