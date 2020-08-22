#pragma once
#include <IO/BitstreamReader.h>

struct RegionwisePacking
{
    struct PackedRegion
    {
        std::uint8_t rwpReservedZero4Bits = 0;
        std::uint8_t transformType = 0;
        bool guardBandFlag = false;
        std::uint32_t projRegionWidth = 0;
        std::uint32_t projRegionHeight = 0;
        std::uint32_t projRegionTop = 0;
        std::uint32_t projRegionLeft = 0;
        std::uint16_t packedRegionWidth = 0;
        std::uint16_t packedRegionHeight = 0;
        std::uint16_t packedRegionTop = 0;
        std::uint16_t packedRegionLeft = 0;

        std::uint8_t leftGbWidth = 0;
        std::uint8_t rightGbWidth = 0;
        std::uint8_t topGbHeight = 0;
        std::uint8_t bottomGbHeight = 0;
        bool gbNotUsedForPredFlag = false;
        std::uint8_t gbType[4];
        std::uint8_t rwpRbReservedZero3Bits = 0;

        PackedRegion() = default;
        explicit PackedRegion(BitstreamReader& reader)
        {
            rwpReservedZero4Bits = reader.readBits<std::uint8_t, 4>();
            transformType = reader.readBits<std::uint8_t, 3>();
            guardBandFlag = reader.readBits<bool, 1>();
            projRegionWidth = reader.readBits<std::uint32_t, 32>();
            projRegionHeight = reader.readBits<std::uint32_t, 32>();
            packedRegionWidth = reader.readBits<std::uint16_t, 16>();
            packedRegionHeight = reader.readBits<std::uint16_t, 16>();
            packedRegionTop = reader.readBits<std::uint16_t, 16>();
            packedRegionLeft = reader.readBits<std::uint16_t, 16>();
            if (guardBandFlag)
            {
                leftGbWidth = reader.readBits<std::uint8_t, 8>();
                rightGbWidth = reader.readBits<std::uint8_t, 8>();
                topGbHeight = reader.readBits<std::uint8_t, 8>();
                bottomGbHeight = reader.readBits<std::uint8_t, 8>();
                gbNotUsedForPredFlag = reader.readBits<bool, 1>();
                for (auto j = 0; j < 4; j++)
                {
                    gbType[j] = reader.readBits<std::uint8_t, 3>();
                }
                rwpRbReservedZero3Bits = reader.readBits<std::uint8_t, 3>();
            }
        }
    };

    bool rwpCancelFlag = false;
    bool rwpPersistenceFlag = false;
    bool constituentPictureMatchingFlag = false;
    std::uint8_t rwpReservedZero5Bits = 0;
    std::uint8_t numPackedRegions = 0;
    std::uint32_t projPictureWidth = 0;
    std::uint32_t projPictureHeight = 0;
    std::uint16_t packedPictureWidth = 0;
    std::uint16_t packedPictureHeight = 0;
    std::vector<PackedRegion> packedRegions;

    RegionwisePacking() = default;
    explicit RegionwisePacking(BitstreamReader& reader)
    {
        rwpCancelFlag = reader.readBits<bool, 1>();
        if (!rwpCancelFlag)
        {
            rwpPersistenceFlag = reader.readBits<bool, 1>();
            constituentPictureMatchingFlag = reader.readBits<bool, 1>();
            rwpReservedZero5Bits = reader.readBits<std::uint8_t, 5>();
            numPackedRegions = reader.readBits<std::uint8_t, 8>();
            projPictureWidth = reader.readBits<std::uint32_t, 32>();
            projPictureHeight = reader.readBits<std::uint32_t, 32>();
            packedPictureHeight = reader.readBits<std::uint16_t, 16>();
            packedPictureWidth = reader.readBits<std::uint16_t, 16>();
            for (auto i = 0; i < numPackedRegions; i++)
            {
                packedRegions.emplace_back(reader);
            }
        }
    }

};


