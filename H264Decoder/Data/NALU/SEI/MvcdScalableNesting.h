#pragma once
#include <IO/BitstreamReader.h>


struct MvcdScalableNesting
{
    struct ViewComponent
    {
        std::uint16_t seiViewId = 0;
        bool seiViewApplicablityFlag = false;

        ViewComponent() = default;
        explicit ViewComponent(BitstreamReader& reader)
        {
            seiViewId = reader.readBits<std::uint16_t, 10>();
            seiViewApplicablityFlag = reader.readBits<bool, 1>();
        }
    };

    struct ViewComponentOp
    {
        std::uint16_t seiOpViewId = 0;
        bool seiOpDepthFlag = false;
        bool seiOpTextureFlag = false;

        ViewComponentOp() = default;
        explicit ViewComponentOp(BitstreamReader& reader, bool opTextureFlag)
        {
            seiOpViewId = reader.readBits<std::uint16_t, 10>();
            if (!opTextureFlag)
            {
                seiOpDepthFlag = reader.readBits<bool, 1>();
                seiOpTextureFlag = reader.readBits<bool, 1>();
            }

        }
    };

    bool operationPointFlag = false;
    bool allViewComponentsInAuFlag = false;
    std::uint32_t numViewComponentsMinus1 = 0;
    std::vector<ViewComponent> viewComponents;

    bool seiOpTextureOnlyFlag = false;
    std::uint32_t numViewComponentsOpMinus1 = 0;
    std::vector<ViewComponentOp> viewComponentOps;

    std::uint8_t seiOpTemporalId = 0;

    std::uint8_t seiNestingZeroBit = 0;

    SEIMessage seiMessage;

    MvcdScalableNesting() = default;
    explicit MvcdScalableNesting(BitstreamReader& reader)
    {
        operationPointFlag = reader.readBits<bool, 1>();
        if (!operationPointFlag)
        {
            allViewComponentsInAuFlag = reader.readBits<bool, 1>();
            if (!allViewComponentsInAuFlag)
            {
                numViewComponentsMinus1 = reader.readExpoGlomb();
                for (auto i = 0; i <= numViewComponentsMinus1; i++)
                {
                    viewComponents.emplace_back(reader);
                }
            }
        }
        else
        {
            seiOpTextureOnlyFlag = reader.readBits<bool, 1>();
            numViewComponentsMinus1 = reader.readExpoGlomb();
            for (auto i = 0; i <= numViewComponentsOpMinus1; i++)
            {
                viewComponentOps.emplace_back(reader);
            }
            seiOpTemporalId = reader.readBits<std::uint8_t, 3>();
        }

        while (!reader.byteAligned())
        {
            seiNestingZeroBit = reader.readBits<std::uint8_t, 1>();
        }

        // TODO: sei message
    }
};


