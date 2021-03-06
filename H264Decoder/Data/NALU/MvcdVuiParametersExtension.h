#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\MvcdOp.h>

struct MvcdVuiParametersExtension
{
    std::uint16_t vuiMvcdNumOpsMinus1 = 0;
    std::vector<MvcdOp> mvcdOps;

    MvcdVuiParametersExtension() = default;
    explicit MvcdVuiParametersExtension(BitstreamReader& reader)
    {
        vuiMvcdNumOpsMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= vuiMvcdNumOpsMinus1; i++)
        {
            mvcdOps.emplace_back(reader);
        }
    }
};

