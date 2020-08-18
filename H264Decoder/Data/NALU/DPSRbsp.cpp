#include "pch.h"
#include "DPSRbsp.h"
#include <Data/DecodingContext.h>

DPSRbsp::DPSRbsp(DecodingContext& context, BitstreamReader& reader)
{
    dpsId = reader.readExpoGlomb();
    predDirection = reader.readExpoGlomb();
    if (predDirection == 0 || predDirection == 1)
    {
        refDpsId0 = reader.readExpoGlomb();
        predWeight0 = 64;
    }
    if (predDirection == 0)
    {
        refDpsId1 = reader.readExpoGlomb();
        predWeight0 = reader.readBits<std::uint8_t, 6>();
    }
    numDepthViewsMinus1 = reader.readExpoGlomb();
    depthRanges = DepthRange{ context, reader, numDepthViewsMinus1 + 1, predDirection, dpsId };
    vspParamFlag = reader.readBits<std::uint8_t, 1>();
    if (vspParamFlag)
    {
        vspParam = VspParam{ reader, numDepthViewsMinus1 + 1, predDirection, dpsId };
    }
    depthParamAdditionalExtensionFlag = reader.readBits<std::uint8_t, 1>();
    nonlinearDepthRepresentationNum = reader.readExpoGlomb();
    for (auto i = 1; i <= nonlinearDepthRepresentationNum; i++)
    {
        nonlinearDepthRepresentationModel.emplace_back(reader.readExpoGlomb());
    }
    if (depthParamAdditionalExtensionFlag)
    {
        while (reader.moreData())
        {
            depthParamAdditionalExtensionDataFlags.emplace_back(reader.readBits<std::uint8_t, 1>());
        }
    }
    rbspTrailingBits = RbspTrailingBits{ reader };
    context.addDPS(*this);
}
