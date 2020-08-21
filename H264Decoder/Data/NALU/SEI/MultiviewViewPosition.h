#pragma once
#include <IO/BitstreamReader.h>


struct MultiviewViewPosition
{
    std::uint16_t numViewsMinus1 = 0;
    std::vector<std::uint16_t> viewPosition;

    bool multiViewPositionExtensionFlag = false;

    MultiviewViewPosition() = default;
    explicit MultiviewViewPosition(BitstreamReader& reader)
    {
        numViewsMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= numViewsMinus1; i++)
        {
            viewPosition.emplace_back(reader.readExpoGlomb());
        }
        multiViewPositionExtensionFlag = reader.readBits<bool, 1>();
    }
};



