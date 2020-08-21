#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/SEI/DepthGridPosition.h>

struct DepthSamplingInfo
{
    struct VideoPlusDepthView
    {
        std::uint32_t depthGridViewId = 0;
        DepthGridPosition depthGridPosition;

        VideoPlusDepthView() = default;
        explicit VideoPlusDepthView(BitstreamReader& reader)
        {
            depthGridViewId = reader.readExpoGlomb();
            depthGridPosition = DepthGridPosition{ reader };
        }
    };

    std::uint16_t dttsrXMul = 0;
    std::uint8_t dttsrXDp = 0;
    std::uint16_t dttsrYMul = 0;
    std::uint8_t dttsrYDp = 0;

    bool perViewDepthGridPosFlag = false;

    std::uint16_t numVideoPlusDepthViewsMinus1 = 0;
    std::vector<VideoPlusDepthView> videoPlusDepthViews;

    DepthGridPosition depthGridPosition;

    DepthSamplingInfo() = default;
    explicit DepthSamplingInfo(BitstreamReader& reader)
    {
        dttsrXMul = reader.readBits<std::uint16_t, 16>();
        dttsrXDp = reader.readBits<std::uint8_t, 4>();
        dttsrYMul = reader.readBits<std::uint16_t, 16>();
        dttsrXDp = reader.readBits<std::uint8_t, 4>();
        perViewDepthGridPosFlag = reader.readBits<bool, 1>();
        if (perViewDepthGridPosFlag)
        {
            numVideoPlusDepthViewsMinus1 = reader.readExpoGlomb();
            for (auto i = 0; i <= numVideoPlusDepthViewsMinus1; i++)
            {
                videoPlusDepthViews.emplace_back(reader);
            }
        }
        else
        {
            depthGridPosition = DepthGridPosition{ reader };
        }
    }
};


