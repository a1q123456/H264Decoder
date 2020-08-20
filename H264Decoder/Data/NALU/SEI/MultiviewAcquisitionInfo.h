#pragma once
#include <IO/BitstreamReader.h>


struct MultiviewAcquisitionInfo
{
    struct ParamSet
    {
        DecimalValue focalLengthX;
        DecimalValue focalLengthY;
        DecimalValue principalPointX;
        DecimalValue principalPointY;
        DecimalValue skew;

        ParamSet() = default;
        explicit ParamSet(BitstreamReader& reader, int precFocalLength, int precPrincipalPoint, int precSkewFactor)
        {
            focalLengthX.sign = reader.readBits<std::uint8_t, 1>();
            focalLengthX.exponent = reader.readBits<std::uint8_t, 6>();
            focalLengthX.mantissa = reader.readBits<std::uint32_t>(getMantisaLength(focalLengthX.exponent, precFocalLength));

            focalLengthY.sign = reader.readBits<std::uint8_t, 1>();
            focalLengthY.exponent = reader.readBits<std::uint8_t, 6>();
            focalLengthY.mantissa = reader.readBits<std::uint32_t>(getMantisaLength(focalLengthY.exponent, precFocalLength));

            principalPointX.sign = reader.readBits<std::uint8_t, 1>();
            principalPointX.exponent = reader.readBits<std::uint8_t, 6>();
            principalPointX.mantissa = reader.readBits<std::uint32_t>(getMantisaLength(principalPointX.exponent, precPrincipalPoint));

            principalPointY.sign = reader.readBits<std::uint8_t, 1>();
            principalPointY.exponent = reader.readBits<std::uint8_t, 6>();
            principalPointY.mantissa = reader.readBits<std::uint32_t>(getMantisaLength(principalPointY.exponent, precPrincipalPoint));

            skew.sign = reader.readBits<std::uint8_t, 1>();
            skew.exponent = reader.readBits<std::uint8_t, 6>();
            skew.mantissa = reader.readBits<std::uint32_t>(getMantisaLength(skew.exponent, precSkewFactor));
        }
    };

    struct ExtrinsicParam
    {
        DecimalValue rotation[4][4];
        DecimalValue translation[4];

        ExtrinsicParam() = default;
        explicit ExtrinsicParam(BitstreamReader& reader, int precRotationParam, int precTranslationParam)
        {
            for (auto j = 1; j <= 3; j++)
            {
                for (auto k = 1; k <= 3; k++)
                {
                    rotation[j][k].sign = reader.readBits<std::uint8_t, 1>();
                    rotation[j][k].exponent = reader.readBits<std::uint8_t, 6>();
                    rotation[j][k].mantissa = reader.readBits<std::uint32_t>(getMantisaLength(rotation[j][k].exponent, precRotationParam));
                }
                translation[j].sign = reader.readBits<std::uint8_t, 1>();
                translation[j].exponent = reader.readBits<std::uint8_t, 6>();
                translation[j].mantissa = reader.readBits<std::uint32_t>(getMantisaLength(translation[j].exponent, precTranslationParam));
            }
        }
    };

    std::uint32_t numViewsMinus1 = 0;
    bool intrinsicParamFlag = false;
    bool extrinsicParamFlag = false;

    bool intrinsicParamsEqual = false;
    std::uint32_t precFocalLength = 0;
    std::uint32_t precPrincipalPoint = 0;
    std::uint32_t precSkewFactor = 0;
    std::vector<ParamSet> paramSets;

    std::uint32_t precRotationParam = 0;
    std::uint32_t precTranslationParam = 0;
    std::vector<ExtrinsicParam> extrinsicParams;

    MultiviewAcquisitionInfo() = default;
    explicit MultiviewAcquisitionInfo(BitstreamReader& reader)
    {
        numViewsMinus1 = reader.readExpoGlomb();
        intrinsicParamFlag = reader.readBits<bool, 1>();
        extrinsicParamFlag = reader.readBits<bool, 1>();

        if (intrinsicParamFlag)
        {
            intrinsicParamsEqual = reader.readBits<bool, 1>();
            precFocalLength = reader.readExpoGlomb();
            precPrincipalPoint = reader.readExpoGlomb();
            precSkewFactor = reader.readExpoGlomb();
            auto numOfParamSets = 0;
            if (intrinsicParamsEqual)
            {
                numOfParamSets = 1;
            }
            else
            {
                numOfParamSets = numViewsMinus1 + 1;
            }
            for (auto i = 0; i < numOfParamSets; i++)
            {
                paramSets.emplace_back(reader, precFocalLength, precPrincipalPoint, precSkewFactor);
            }
        }
        if (extrinsicParamFlag)
        {
            precRotationParam = reader.readExpoGlomb();
            precTranslationParam = reader.readExpoGlomb();

            for (auto i = 0; i <= numViewsMinus1; i++)
            {
                extrinsicParams.emplace_back(reader, precRotationParam, precTranslationParam);
            }
        }

    }
};


