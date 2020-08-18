#pragma once
#include <IO/BitstreamReader.h>


struct PanScanRect
{
    struct RectType
    {
        std::int16_t leftOffset = 0;
        std::int16_t rightOffset = 0;
        std::int16_t topOffset = 0;
        std::int16_t bottomOffset = 0;

    };

    std::uint8_t panScanRectId = 0;
    bool panScanRectCancelFlag = false;

    std::uint8_t panScanCntMinus1 = 0;
    std::vector<RectType> panScanRects;

    std::uint8_t panScanRectRepetitionPeriod = 0;

    PanScanRect() = default;
    explicit PanScanRect(BitstreamReader& reader, int)
    {
        panScanRectId = reader.readExpoGlomb();
        panScanRectCancelFlag = reader.readBits<std::uint8_t, 1>();
        if (!panScanRectCancelFlag)
        {
            panScanCntMinus1 = reader.readExpoGlomb();
            for (auto i = 0; i < panScanCntMinus1; i++)
            {
                RectType rect;
                rect.leftOffset = reader.readSignedExpoGlomb();
                rect.rightOffset = reader.readSignedExpoGlomb();
                rect.topOffset = reader.readSignedExpoGlomb();
                rect.bottomOffset = reader.readSignedExpoGlomb();
                panScanRects.emplace_back(rect);
            }
            panScanRectRepetitionPeriod = reader.readExpoGlomb();
        }
    }
};


