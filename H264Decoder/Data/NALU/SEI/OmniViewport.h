#pragma once
#include <IO/BitstreamReader.h>


struct OmniViewport
{
    struct OmniViewportData
    {
        std::int32_t omniViewportAzimuthCentre = 0;
        std::int32_t omniViewportElvationCentre = 0;
        std::int32_t omniViewportTiltCentre = 0;
        std::uint32_t omniViewportHorRange = 0;
        std::uint32_t omniViewportVerRange = 0;

        OmniViewportData() = default;
        explicit OmniViewportData(BitstreamReader& reader)
        {
            omniViewportAzimuthCentre = reader.readBits<std::int32_t, 32>();
            omniViewportElvationCentre = reader.readBits<std::int32_t, 32>();
            omniViewportTiltCentre = reader.readBits<std::int32_t, 32>();
            omniViewportHorRange = reader.readBits<std::uint32_t, 32>();
            omniViewportVerRange = reader.readBits<std::uint32_t, 32>();
        }

    };

    std::uint16_t omniViewPortId = 0;
    bool omniViewportCancelFlag = false;
    bool omniViewportPersistenceFlag = false;
    std::uint8_t omniViewportCntMinus1 = 0;
    std::vector<OmniViewportData> omniViewportData;

    OmniViewport() = default;
    explicit OmniViewport(BitstreamReader& reader)
    {
        omniViewPortId = reader.readBits<std::uint16_t, 10>();
        omniViewportCancelFlag = reader.readBits < bool, 1>();
        if (!omniViewportCancelFlag)
        {
            omniViewportPersistenceFlag = reader.readBits<bool, 1>();
            omniViewportCntMinus1 = reader.readBits<std::uint8_t, 4>();
            for (auto i = 0; i <= omniViewportCntMinus1; i++)
            {
                omniViewportData.emplace_back(reader);
            }
        }
    }

};


