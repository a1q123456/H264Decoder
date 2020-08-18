#pragma once
#include <Data/Byte.h>
#include <IO/BitstreamReader.h>
#include <functional>
#include <Data/NaluTypes.h>
#include <Data/NALU/NALUnitHeaderSvcExtension.h>
#include <Data/NALU/NALUnitHeader3DavcExtension.h>
#include <Data/NALU/NALUnitHeaderMvcExtension.h>


struct NALUnit
{
    std::uint8_t forbiddenZeroBit = 0;
    std::uint8_t nalRefIdc = 0;
    NaluTypes nalUnitType;
    bool svcExtensionFlag = false;
    bool avc3DExtensionFlag = false;

    NALUnitHeaderSvcExtension nalUnitHeaderSvcExtension;
    NALUnitHeader3DavcExtension nalUnitHeader3DavcExtension;
    NALUnitHeaderMvcExtension nalUnitHeaderMvcExtension;

    std::shared_ptr<std::uint8_t> rbsp;
};






