#pragma once
#include <IO/BitstreamReader.h>

struct EquirectangularProjection
{
    bool erpCancelFlag = false;
    bool erpPresistenceFlag = false;
    bool erpPaddingFlag = false;
    std::uint16_t erpReservedZero2Bits = 0;

    std::uint16_t gpErpType = 0;
    std::uint8_t leftGbErpWidth = 0;
    std::uint8_t rightGbErpWidth = 0;

    EquirectangularProjection() = default;
    explicit EquirectangularProjection(BitstreamReader& reader)
    {
        erpCancelFlag = reader.readBits<bool, 1>();
        if (!erpCancelFlag)
        {
            erpPresistenceFlag = reader.readBits<bool, 1>();
            erpPaddingFlag = reader.readBits<bool, 1>();
            erpReservedZero2Bits = reader.readBits<std::uint16_t, 2>();
            if (erpPaddingFlag)
            {
                gpErpType = reader.readBits<std::uint16_t, 3>();
                leftGbErpWidth = reader.readBits<std::uint8_t, 8>();
                rightGbErpWidth = reader.readBits<std::uint8_t, 8>();
            }
        }
    }

};




