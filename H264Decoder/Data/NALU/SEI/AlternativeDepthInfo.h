#pragma once
#include <IO/BitstreamReader.h>


struct AlternativeDepthInfo
{
    struct ZInfo
    {
        DecimalValue gvdZNear;
        DecimalValue gvdZFar;

        ZInfo() = default;
        explicit ZInfo(BitstreamReader& reader)
        {
            gvdZNear.sign = reader.readBits<std::uint8_t, 1>();
            gvdZNear.exponent = reader.readBits<std::uint8_t, 7>();
            auto gvdZNearMLen = reader.readBits<std::uint8_t, 5>();
            gvdZNear.mantissa = reader.readBits<std::uint32_t>(gvdZNearMLen);

            gvdZFar.sign = reader.readBits<std::uint8_t, 1>();
            gvdZFar.exponent = reader.readBits<std::uint8_t, 7>();
            auto gvdZFarMLen = reader.readBits<std::uint8_t, 5>();
            gvdZFar.mantissa = reader.readBits<std::uint32_t>(gvdZFarMLen);
        }
    };

    struct IntrinsicParam
    {
        DecimalValue gvdFocalLengthX;
        DecimalValue gvdFocalLengthY;
        DecimalValue gvdPrincipalPointX;
        DecimalValue gvdPrincipalPointY;

        DecimalValue rotation[3][3];
        DecimalValue translation;

        IntrinsicParam() = default;
        explicit IntrinsicParam(BitstreamReader& reader,
            int precGvdFocalLength,
            int precGvdPrincipalPoint,
            bool rotationGvdFlag,
            int precGvdRotationParam,
            bool translationGvdFlag,
            int precGvdTranslationParam


            )
        {
            gvdFocalLengthX.sign = reader.readBits<std::uint8_t, 1>();
            gvdFocalLengthX.exponent = reader.readBits<std::uint8_t, 6>();
            auto focalManXLen = 0;
            if (gvdFocalLengthX.exponent == 0)
            {
                focalManXLen = std::max(0, precGvdFocalLength - 30);
            }
            else
            {
                focalManXLen = std::max(0, gvdFocalLengthX.exponent + precGvdFocalLength - 31);
            }
            gvdFocalLengthX.mantissa = reader.readBits<std::uint32_t>(focalManXLen);


            gvdFocalLengthY.sign = reader.readBits<std::uint8_t, 1>();
            gvdFocalLengthY.exponent = reader.readBits<std::uint8_t, 6>();
            auto focalManYLen = 0;
            if (gvdFocalLengthY.exponent == 0)
            {
                focalManYLen = std::max(0, precGvdFocalLength - 30);
            }
            else
            {
                focalManYLen = std::max(0, gvdFocalLengthY.exponent + precGvdFocalLength - 31);
            }
            gvdFocalLengthY.mantissa = reader.readBits<std::uint32_t>(focalManYLen);


            gvdPrincipalPointX.sign = reader.readBits<std::uint8_t, 1>();
            gvdPrincipalPointX.exponent = reader.readBits<std::uint8_t, 6>();
            auto principalPointManXLen = 0;
            if (gvdPrincipalPointX.exponent == 0)
            {
                principalPointManXLen = std::max(0, precGvdPrincipalPoint - 30);
            }
            else
            {
                principalPointManXLen = std::max(0, gvdPrincipalPointX.exponent + precGvdFocalLength - 31);
            }
            gvdPrincipalPointX.mantissa = reader.readBits<std::uint32_t>(principalPointManXLen);


            gvdPrincipalPointY.sign = reader.readBits<std::uint8_t, 1>();
            gvdPrincipalPointY.exponent = reader.readBits<std::uint8_t, 6>();
            auto principalPointManYLen = 0;
            if (gvdPrincipalPointY.exponent == 0)
            {
                principalPointManYLen = std::max(0, precGvdPrincipalPoint - 30);
            }
            else
            {
                principalPointManYLen = std::max(0, gvdPrincipalPointY.exponent + precGvdFocalLength - 31);
            }
            gvdPrincipalPointY.mantissa = reader.readBits<std::uint32_t>(principalPointManYLen);


            if (rotationGvdFlag)
            {
                for (auto i = 0; i < 3; i++)
                {
                    for (auto j = 0; j < 3; j++)
                    {
                        rotation[i][j].sign = reader.readBits<std::uint8_t, 1>();
                        rotation[i][j].exponent = reader.readBits<std::uint8_t, 6>();
                        auto len = 0;
                        if (rotation[i][j].exponent == 0)
                        {
                            len = std::max(0, precGvdRotationParam - 30);
                        }
                        else
                        {
                            len = std::max(0, rotation[i][j].exponent + precGvdRotationParam - 31);
                        }
                        rotation[i][j].mantissa = reader.readBits<std::uint32_t>(len);
                    }
                }
            }
            if (translationGvdFlag)
            {
                translation.sign = reader.readBits<std::uint8_t, 1>();
                translation.exponent = reader.readBits<std::uint8_t, 6>();
                auto len = 0;
                if (translation.exponent == 0)
                {
                    len = std::max(0, precGvdTranslationParam - 30);
                }
                else
                {
                    len = std::max(0, translation.exponent + precGvdTranslationParam - 31);
                }
                translation.mantissa = reader.readBits<std::uint32_t>(len);
            }
        }
    };

    std::uint32_t depthType = 0;
    std::uint16_t numConstituentViewsGvdMinus1 = 0;
    bool depthPresentGvdFlag = false;
    bool zGvdFlag = false;
    bool intrinsicParamGvdFlag = false;
    bool rotationGvdFlag = false;
    bool translationGvdFlag = false;
    std::vector<ZInfo> zInfos;

    std::uint32_t precGvdFocalLength = 0;
    std::uint32_t precGvdPrincipalPoint = 0;

    std::uint32_t precGvdRotationParam = 0;
    std::uint32_t precGvdTranslationParam = 0;
    std::vector<IntrinsicParam> intrinsicParams;



    AlternativeDepthInfo() = default;
    explicit AlternativeDepthInfo(BitstreamReader& reader)
    {
        depthType = reader.readExpoGlomb();
        if (depthType == 0)
        {
            numConstituentViewsGvdMinus1 = reader.readExpoGlomb();
            depthPresentGvdFlag = reader.readBits<bool, 1>();
            zGvdFlag = reader.readBits<bool, 1>();
            intrinsicParamGvdFlag = reader.readBits<bool, 1>();
            rotationGvdFlag = reader.readBits<bool, 1>();
            translationGvdFlag = reader.readBits<bool, 1>();
            if (zGvdFlag)
            {
                for (auto i = 0; i <= numConstituentViewsGvdMinus1; i++)
                {
                    zInfos.emplace_back(reader);
                }
            }
            if (intrinsicParamGvdFlag)
            {
                precGvdFocalLength = reader.readExpoGlomb();
                precGvdPrincipalPoint = reader.readExpoGlomb();
            }
            if (rotationGvdFlag)
            {
                precGvdRotationParam = reader.readExpoGlomb();
            }
            if (translationGvdFlag)
            {
                precGvdTranslationParam = reader.readExpoGlomb();
            }
            for (auto i = 0; i <= numConstituentViewsGvdMinus1; i++)
            {
                if (intrinsicParamGvdFlag)
                {
                    intrinsicParams.emplace_back(reader,
                        precGvdFocalLength,
                        precGvdPrincipalPoint,
                        rotationGvdFlag,
                        precGvdRotationParam,
                        translationGvdFlag,
                        precGvdTranslationParam);
                }
            }
        }
    }
};


