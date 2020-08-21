#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\VuiMvcOp.h>


struct MvcVuiParametersExtension
{
    std::uint16_t vuiMvcNumOpsMinus1 = 0;
    std::vector<VuiMvcOp> vuiMvcOps;

    MvcVuiParametersExtension() = default;
    explicit MvcVuiParametersExtension(BitstreamReader& reader)
    {
        vuiMvcNumOpsMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= vuiMvcNumOpsMinus1; i++)
        {
            vuiMvcOps.emplace_back(reader);
        }
    }
};


