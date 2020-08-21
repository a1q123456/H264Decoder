#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/SEI/SEIMessage.h>


struct SEIRbsp
{
    std::vector<SEIMessage> seiMessage;
    RbspTrailingBits rbspTrailingBits;

    SEIRbsp() = default;
    explicit SEIRbsp(DecodingContext& context, BitstreamReader& reader, NALUnit& nalu)
    {
        do
        {
            seiMessage.emplace_back(context, reader, nalu);
        } while (reader.moreData());
    }
};


