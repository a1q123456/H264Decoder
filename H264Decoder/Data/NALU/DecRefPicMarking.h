#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NaluTypes.h>

struct DecRefPicMarking
{
    bool noOutputOfPriorPicsFlag = false;
    bool longTermReferenceFlag = false;

    bool adaptiveRefPicMarkingModeFlag = false;

    std::uint16_t memoryManagementControlOperation = 0;
    std::uint16_t differenceOfPicNumsMinus1 = 0;
    std::uint16_t longTermPicNum = 0;
    std::uint16_t longTermFrameIdx = 0;
    std::uint16_t maxLongTermFrameIdxPlus1 = 0;

    DecRefPicMarking() = default;
    explicit DecRefPicMarking(NaluTypes nalType, BitstreamReader& reader);
};


