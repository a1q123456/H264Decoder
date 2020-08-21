#pragma once
#include <IO/BitstreamReader.h>

struct AnchorRef
{
    std::uint16_t numAnchorRefsL0 = 0;
    std::vector<std::uint16_t> anchorRefL0;

    std::uint16_t numAnchorRefsL1 = 0;
    std::vector<std::uint16_t> anchorRefl1;

    AnchorRef() = default;
    explicit AnchorRef(BitstreamReader& reader)
    {
        ReadAnchorRef(reader, numAnchorRefsL0, anchorRefL0);
        ReadAnchorRef(reader, numAnchorRefsL1, anchorRefl1);
    }

private:
    void ReadAnchorRef(BitstreamReader& reader, std::uint16_t& num, std::vector<std::uint16_t>& ref)
    {
        num = reader.readExpoGlomb();
        for (auto i = 0; i < num; i++)
        {
            ref.emplace_back(reader.readExpoGlomb());
        }
    }
};


