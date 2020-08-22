#pragma once
#include <IO/BitstreamReader.h>

struct SEIPrefixIndication
{
    struct SEIPrefixIndicationData
    {
        std::uint16_t numBitsInPrefixIndicationMinus1 = 0;
        std::vector<std::uint8_t> seiPrefixDataBits;
        std::uint8_t byteAlignmentBitEqualToOne = 0;

        SEIPrefixIndicationData() = default;
        explicit SEIPrefixIndicationData(BitstreamReader& reader)
        {
            numBitsInPrefixIndicationMinus1 = reader.readBits<std::uint16_t, 16>();
            for (auto j = 0; j <= numBitsInPrefixIndicationMinus1; j++)
            {
                seiPrefixDataBits.emplace_back(reader.readBits<std::uint8_t, 1>());
            }
            while (!reader.byteAligned())
            {
                byteAlignmentBitEqualToOne = reader.readBits<std::uint8_t, 1>();
                if (byteAlignmentBitEqualToOne != 1)
                {
                    throw std::runtime_error("parse error");
                }
            }
        }

    };

    std::uint16_t prefixSEIPayloadType = 0;
    std::uint8_t numSEIPrefixIndicationsMinus1 = 0;
    std::vector<SEIPrefixIndicationData> seiPrefixIndications;

    SEIPrefixIndication() = default;
    explicit SEIPrefixIndication(BitstreamReader& reader)
    {
        prefixSEIPayloadType = reader.readBits<std::uint16_t, 16>();
        numSEIPrefixIndicationsMinus1 = reader.readBits<std::uint8_t, 8>();
        for (auto i = 0; i <= numSEIPrefixIndicationsMinus1; i++)
        {
            seiPrefixIndications.emplace_back(reader);
        }
    }

};

