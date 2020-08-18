#pragma once
#include <IO/BitstreamReader.h>


struct SvcVuiParametersExtension
{
    std::uint8_t vuiExtNumEntriesMinus1 = 0;

    std::vector<VuiExtInfo> vuiExtInfo;

    SvcVuiParametersExtension() = default;
    explicit SvcVuiParametersExtension(BitstreamReader& reader)
    {
        vuiExtNumEntriesMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= vuiExtNumEntriesMinus1; i++)
        {
            vuiExtInfo.emplace_back(VuiExtInfo{ reader });
        }
    }
};




