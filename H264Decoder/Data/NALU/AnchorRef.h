#pragma once
#include <IO/BitstreamReader.h>

struct AnchorRef
{
    std::uint8_t numAnchorRefsL0 = 0;
    std::vector<std::uint8_t> anchorRefL0;

    std::uint8_t numAnchorRefsL1 = 0;
    std::vector<std::uint8_t> anchorRefl1;

    AnchorRef() = default;
    explicit AnchorRef(BitstreamReader& reader)
    {
        ReadAnchorRef(reader, numAnchorRefsL0, anchorRefL0);
        ReadAnchorRef(reader, numAnchorRefsL1, anchorRefl1);
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


