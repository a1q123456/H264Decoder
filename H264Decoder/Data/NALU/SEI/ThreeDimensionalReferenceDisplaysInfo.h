#pragma once
#include <IO/BitstreamReader.h>


struct ThreeDimensionalReferenceDisplaysInfo
{
    struct RefDisplay
    {
        DecimalValue refBaseline;
        DecimalValue refDisplayWidth;
        DecimalValue refViewingDistance;
        bool additionalShitPresentFlag = false;
        std::uint16_t numSampleShiftPlus512 = 0;

        RefDisplay() = default;
        explicit RefDisplay(BitstreamReader& reader, bool refViewingDistanceFlag, int precRefDisplayWidth)
        {
            int v = 0;
            refBaseline.sign = 1;
            refBaseline.exponent = reader.readBits<std::uint8_t, 6>();
            if (refBaseline.exponent == 0)
            {
                v = std::max(0, precRefDisplayWidth - 30);
            }
            else if (0 < refBaseline.exponent && refBaseline.exponent < 63)
            {
                v = std::max(0, refBaseline.exponent + precRefDisplayWidth - 31);
            }
            else
            {
                v = 0;
            }
            refBaseline.mantissa = reader.readBits<std::uint32_t>(v);

            refDisplayWidth.sign = 1;
            refDisplayWidth.exponent = reader.readBits<std::uint8_t, 8>();

            if (refDisplayWidth.exponent == 0)
            {
                v = std::max(0, precRefDisplayWidth - 30);
            }
            else if (0 < refDisplayWidth.exponent && refDisplayWidth.exponent < 63)
            {
                v = std::max(0, refDisplayWidth.exponent + precRefDisplayWidth - 31);
            }
            else
            {
                v = 0;
            }
            refDisplayWidth.mantissa = reader.readBits<std::uint32_t>(v);
            if (refViewingDistanceFlag)
            {
                refViewingDistance.sign = 1;
                refViewingDistance.exponent = reader.readBits<std::uint8_t, 6>();
                if (refViewingDistance.exponent == 0)
                {
                    v = std::max(0, precRefDisplayWidth - 30);
                }
                else if (0 < refViewingDistance.exponent && refViewingDistance.exponent < 63)
                {
                    v = std::max(0, refViewingDistance.exponent + precRefDisplayWidth - 31);
                }
                else
                {
                    v = 0;
                }
                refViewingDistance.mantissa = reader.readBits<std::uint32_t>(v);
            }
            additionalShitPresentFlag = reader.readBits<bool, 1>();
            if (additionalShitPresentFlag)
            {
                numSampleShiftPlus512 = reader.readBits<std::uint16_t, 10>();
            }
        }
    };

    std::uint32_t precRefBaseline = 0;
    std::uint32_t precRefDisplayWidth = 0;
    bool refViewingDistanceFlag = false;
    std::uint32_t precRefViewingDist = 0;
    std::uint32_t numRefDisplaysMinus1 = 0;
    std::vector<RefDisplay> refDisplays;
    bool threeDimensionalReferenceDisplaysExtensionFlag = false;

    ThreeDimensionalReferenceDisplaysInfo() = default;
    explicit ThreeDimensionalReferenceDisplaysInfo(BitstreamReader& reader)
    {
        precRefBaseline = reader.readExpoGlomb();
        precRefDisplayWidth = reader.readExpoGlomb();
        refViewingDistanceFlag = reader.readBits<bool, 1>();

        if (refViewingDistanceFlag)
        {
            precRefViewingDist = reader.readExpoGlomb();
        }
        numRefDisplaysMinus1 = reader.readExpoGlomb();
        auto numRefDisplays = numRefDisplaysMinus1 + 1;
        for (auto i = 0; i < numRefDisplays; i++)
        {
            refDisplays.emplace_back(reader, refViewingDistanceFlag);
        }
    }
};



