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
    std::uint8_t spsId = 0;
    std::vector<Data> nalHrdBpData;
    std::vector<Data> vclHrdBpData;

    BufferingPeriod() = default;
    explicit BufferingPeriod(DecodingContext& context, BitstreamReader& reader, int payloadSize)
    {
        spsId = reader.readExpoGlomb();
        auto iter = context.spsContext.find(spsId);
        if (iter == context.spsContext.end())
        {
            throw std::runtime_error("sps id not found");
        }
        if (iter->second.spsData.vuiParameters.nalHrdParametersPresentFlag || context.applicationDeterminedValues.nalHrdBpPresentFlag)
        {
            auto len = iter->second.spsData.vuiParameters.hrdParameters.initialCPBRemovalDelayLengthMinus1 + 1;
            for (auto i = 0; i <= iter->second.spsData.vuiParameters.hrdParameters.cpbCntMinus1; i++)
            {
                nalHrdBpData.emplace_back(Data{ reader.readBits<std::uint8_t>(len), reader.readBits<std::uint8_t>(len) });
            }
        }
        if (iter->second.spsData.vuiParameters.vclHrdParametersPresentFlag || context.applicationDeterminedValues.vclHrdBpPresentFlag)
        {
            auto len = iter->second.spsData.vuiParameters.hrdParameters.initialCPBRemovalDelayLengthMinus1 + 1;
            for (auto i = 0; i <= iter->second.spsData.vuiParameters.hrdParameters.cpbCntMinus1; i++)
            {
                vclHrdBpData.emplace_back(Data{ reader.readBits<std::uint8_t>(len), reader.readBits<std::uint8_t>(len) });
            }
        }
    }

};


