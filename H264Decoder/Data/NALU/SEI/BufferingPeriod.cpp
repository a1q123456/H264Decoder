#include "pch.h"
#include "BufferingPeriod.h"
#include <Data/DecodingContext.h>

BufferingPeriod::BufferingPeriod(DecodingContext& context, BitstreamReader& reader, int payloadSize)
{
    spsId = reader.readExpoGlomb();
    auto sps = context.findSPS(spsId);
    if (sps.vuiParameters.nalHrdParametersPresentFlag || context.applicationDeterminedValues.nalHrdBpPresentFlag)
    {
        auto len = sps.vuiParameters.hrdParameters.initialCPBRemovalDelayLengthMinus1 + 1;
        for (auto i = 0; i <= sps.vuiParameters.hrdParameters.cpbCntMinus1; i++)
        {
            nalHrdBpData.emplace_back(Data{ reader.readBits<std::uint8_t>(len), reader.readBits<std::uint8_t>(len) });
        }
    }
    if (sps.vuiParameters.vclHrdParametersPresentFlag || context.applicationDeterminedValues.vclHrdBpPresentFlag)
    {
        auto len = sps.vuiParameters.hrdParameters.initialCPBRemovalDelayLengthMinus1 + 1;
        for (auto i = 0; i <= sps.vuiParameters.hrdParameters.cpbCntMinus1; i++)
        {
            vclHrdBpData.emplace_back(Data{ reader.readBits<std::uint8_t>(len), reader.readBits<std::uint8_t>(len) });
        }
    }
}
