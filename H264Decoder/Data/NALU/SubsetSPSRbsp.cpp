#include "pch.h"
#include "SubsetSPSRbsp.h"
#include <Data/DecodingContext.h>

SubsetSPSRbsp::SubsetSPSRbsp(DecodingContext context, BitstreamReader& reader)
{
    spsData = SPSData{ reader };

    if (spsData.profileIdc == 83 || spsData.profileIdc == 86)
    {
        spsSvcExtension = SeqParameterSetSvcExtension{ reader, spsData.chromaArrayType };

        svcVuiParametersPresentFlag = reader.readBits<std::uint8_t, 1>();
        if (svcVuiParametersPresentFlag)
        {
            svcVuiParametersExtension = SvcVuiParametersExtension{ reader };
        }
    }
    else if (spsData.profileIdc == 118 || spsData.profileIdc == 128 || spsData.profileIdc == 134)
    {
        auto bitEqualToOne = reader.readBits<std::uint8_t, 1>();
        if (bitEqualToOne != 1)
        {
            throw std::runtime_error("not supported");
        }
        seqParameterSetMVCExtension = SpsMvcExtension{ reader, spsData.profileIdc };
        mvcVuiParametersPresentFlag = reader.readBits<std::uint8_t, 1>();
        if (mvcVuiParametersPresentFlag)
        {
            mvcVuiParametersExtension = MvcVuiParametersExtension{ reader };
        }
    }
    else if (spsData.profileIdc == 138)
    {
        auto bitEqualToOne = reader.readBits<std::uint8_t, 1>();
        if (bitEqualToOne != 1)
        {
            throw std::runtime_error("not supported");
        }
        spsMvcdExtension = SpsMvcdExtension{ reader };
        sps3davcExtension = Sps3DavcExtension{ context, reader, context.currentDPS().dpsRbsp.numDepthViewsMinus1 + 1 };
    }
    additionalExtension2Flag = reader.readBits<std::uint8_t, 1>();
    if (additionalExtension2Flag)
    {
        while (reader.moreData())
        {
            additionalExtension2DataFlags.push_back(reader.readBits<std::uint8_t, 1>());
        }
    }
    rbspTrailingBits = RbspTrailingBits{ reader };
}
