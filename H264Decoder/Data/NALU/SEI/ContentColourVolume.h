#pragma once
#include <IO/BitstreamReader.h>

struct ContentColourVolume
{
    struct PrimariesValue
    {
        std::int32_t ccvPrimariesX = 0;
        std::int32_t ccvPrimariesY = 0;

        PrimariesValue() = default;
        explicit PrimariesValue(BitstreamReader& reader)
        {
            ccvPrimariesX = reader.readBits<std::int32_t, 32>();
            ccvPrimariesY = reader.readBits<std::int32_t, 32>();
        }
    };

    bool ccvCancelFlag = false;

    bool ccvPersistenceFlag = false;
    bool ccvPrimariesPresentFlag = false;
    bool ccvMinLuminanceValuePresentFlag = false;
    bool ccvMaxLuminanceValuePresentFlag = false;
    bool ccvAvgLuminanceValuePresentFlag = false;

    std::uint16_t ccvReservedZero2Bits = 0;
    PrimariesValue ccvPrimaries[3];

    std::uint32_t ccvMinLuminanceValue = 0;
    std::uint32_t ccvMaxLuminanceValue = 0;
    std::uint32_t ccvAvgLuminanceValue = 0;

    ContentColourVolume() = default;
    explicit ContentColourVolume(BitstreamReader& reader)
    {
        ccvCancelFlag = reader.readBits<bool, 1>();
        if (!ccvCancelFlag)
        {
            ccvPersistenceFlag = reader.readBits<bool, 1>();
            ccvPrimariesPresentFlag = reader.readBits<bool, 1>();
            ccvMinLuminanceValuePresentFlag = reader.readBits<bool, 1>();
            ccvMaxLuminanceValuePresentFlag = reader.readBits<bool, 1>();
            ccvAvgLuminanceValue = reader.readBits<bool, 1>();
            ccvReservedZero2Bits = reader.readBits<std::uint16_t, 2>();

            if (ccvPrimariesPresentFlag)
            {
                for (auto c = 0; c < 3; c++)
                {
                    ccvPrimaries[0] = PrimariesValue{ reader };
                }
            }
            if (ccvMinLuminanceValuePresentFlag)
            {
                ccvMinLuminanceValue = reader.readBits<std::uint32_t, 32>();
            }
            if (ccvMaxLuminanceValuePresentFlag)
            {
                ccvMaxLuminanceValue = reader.readBits<std::uint32_t, 32>();
            }
            if (ccvAvgLuminanceValuePresentFlag)
            {
                ccvAvgLuminanceValue = reader.readBits<std::uint32_t, 32>();
            }
        }

    }

};


