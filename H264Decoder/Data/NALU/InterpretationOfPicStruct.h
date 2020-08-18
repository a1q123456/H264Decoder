#pragma once
#include <IO/BitstreamReader.h>

struct SliceHeader;
struct CurrentPictureContext;
struct VuiParameters;

struct InterpretationOfPicStruct
{
    int value = 0;
    const char* indicatedDisplayOfPicture = nullptr;
    std::function<bool(const SliceHeader&, const CurrentPictureContext& cpc, const VuiParameters& vui)> isSatisfiesRestriction;
    int numClockTs = 0;

    InterpretationOfPicStruct() = default;

    template<typename TFunc>
    InterpretationOfPicStruct(int value, const char* indicatedDisplayOfPicture, TFunc&& cb, int numClockTs) :
        value(value),
        indicatedDisplayOfPicture(indicatedDisplayOfPicture),
        isSatisfiesRestriction(std::forward<TFunc>(cb)),
        numClockTs(numClockTs)
    {
    }
};


