#pragma once
#include <IO/BitstreamReader.h>
#include <Data/DecodingContext.h>

struct BufferingPeriod
{
    struct Data
    {
        std::uint8_t initialCpbRemovalDelay = 0;
        std::uint8_t initialCpbRemovalDelayOffset = 0;

    };
    std::uint16_t spsId = 0;
    std::vector<Data> nalHrdBpData;
    std::vector<Data> vclHrdBpData;

    BufferingPeriod() = default;
    explicit BufferingPeriod(DecodingContext& context, BitstreamReader& reader, int payloadSize)
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

};


