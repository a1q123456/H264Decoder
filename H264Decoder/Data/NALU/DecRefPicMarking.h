#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NaluTypes.h>

struct DecRefPicMarking
{
    bool noOutputOfPriorPicsFlag = false;
    bool longTermReferenceFlag = false;

    bool adaptiveRefPicMarkingModeFlag = false;

    std::uint8_t memoryManagementControlOperation = 0;
    std::uint8_t differenceOfPicNumsMinus1 = 0;
    std::uint8_t longTermPicNum = 0;
    std::uint8_t longTermFrameIdx = 0;
    std::uint8_t maxLongTermFrameIdxPlus1 = 0;

    DecRefPicMarking() = default;
    explicit DecRefPicMarking(NaluTypes nalType, BitstreamReader& reader);
};


