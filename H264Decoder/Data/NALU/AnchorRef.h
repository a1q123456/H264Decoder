#pragma once
#include <IO/BitstreamReader.h>

struct AnchorRef
{
    std::uint8_t numAnchorRefsl0 = 0;
    std::vector<std::uint8_t> anchorRefl0;

    std::uint8_t numAnchorRefsl1 = 0;
    std::vector<std::uint8_t> anchorRefl1;

    AnchorRef() = default;
    explicit AnchorRef(BitstreamReader& reader)
    {
        ReadAnchorRef(reader, numAnchorRefsl0, anchorRefl0);
        ReadAnchorRef(reader, numAnchorRefsl1, anchorRefl1);
    }

private:
    void ReadAnchorRef(BitstreamReader& reader, std::uint8_t& num, std::vector<std::uint8_t>& ref)
    {
        num = reader.readExpoGlomb();
        for (auto i = 0; i < num; i++)
        {
            ref.emplace_back(reader.readExpoGlomb());
        }
    }
};


