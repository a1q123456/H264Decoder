#pragma once
#include <IO/BitstreamReader.h>


struct ColourRemappingInfo
{

    struct LutValues
    {
        std::uint32_t codedValue = 0;
        std::uint32_t targetValue = 0;

        LutValues() = default;
        explicit LutValues(BitstreamReader& reader, int inputDepth, int outputDepth)
        {
            codedValue = reader.readBits<std::uint32_t>(((inputDepth + 7) >> 3) << 3);
            targetValue = reader.readBits<std::uint32_t>(((outputDepth + 7) >> 3) << 3);
        }
    };

    std::uint16_t colourRemapId = 0;
    bool colourRemapCancelFlag = false;
    std::uint16_t colourRemapRepetitionPeriod = 0;
    bool colourRemapVideoSignalInfoPresentFlag = false;
    bool colourRemapFullRangeFlag = false;
    std::uint8_t colourRemapPrimaries = 0;
    std::uint8_t colourRemapTransferFunction = 0;
    std::uint8_t clourRemapMatrixCefficients = 0;

    std::uint8_t colourRemapInputBitDepth = 0;
    std::uint8_t colourRemapOutputBitDepth = 0;

    std::vector<LutValues> preLutValues[3];

    bool colourRemapMatrixPresentFlag = false;
    std::uint8_t log2MatrixDenom = 0;
    std::int16_t colourRemapCoeffs[3][3];


    std::vector<LutValues> postLutValues[3];

    ColourRemappingInfo() = default;
    explicit ColourRemappingInfo(BitstreamReader& reader)
    {
        colourRemapId = reader.readExpoGlomb();
        colourRemapCancelFlag = reader.readBits<bool, 1>();
        if (!colourRemapCancelFlag)
        {
            colourRemapRepetitionPeriod = reader.readExpoGlomb();
            colourRemapVideoSignalInfoPresentFlag = reader.readBits<bool, 1>();
            if (colourRemapVideoSignalInfoPresentFlag)
            {
                colourRemapFullRangeFlag = reader.readBits<bool, 1>();
                colourRemapPrimaries = reader.readBits<std::uint8_t, 8>();
                colourRemapTransferFunction = reader.readBits<std::uint8_t, 8>();
                colourRemapMatrixPresentFlag = reader.readBits<std::uint8_t, 8>();
            }
            colourRemapInputBitDepth = reader.readBits<std::uint8_t, 8>();
            colourRemapOutputBitDepth = reader.readBits<std::uint8_t, 8>();
            for (auto c = 0; c < 3; c++)
            {
                auto preLutNumValMinus1 = reader.readBits<std::uint8_t, 8>();
                if (preLutNumValMinus1 >= 0)
                {
                    for (auto i = 0; i <= preLutNumValMinus1; i++)
                    {
                        preLutValues[i].emplace_back(reader, colourRemapInputBitDepth, colourRemapOutputBitDepth);
                    }
                }
            }

            colourRemapMatrixPresentFlag = reader.readBits<bool, 1>();
            if (colourRemapMatrixPresentFlag)
            {
                log2MatrixDenom = reader.readBits<std::uint8_t, 4>();
                for (auto c = 0; c < 3; c++)
                {
                    for (auto i = 0; i < 3; i++)
                    {
                        colourRemapCoeffs[c][i] = reader.readSignedExpoGlomb();
                    }
                }
            }

            for (auto c = 0; c < 3; c++)
            {
                auto postLutNumValMinus1 = 0;
                if (postLutNumValMinus1 >= 0)
                {
                    for (auto i = 0; i <= postLutNumValMinus1; i++)
                    {
                        postLutValues[i].emplace_back(reader, colourRemapOutputBitDepth, colourRemapOutputBitDepth);
                    }
                }
            }
        }
    }

};


