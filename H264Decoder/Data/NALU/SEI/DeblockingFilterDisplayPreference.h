#pragma once
#include <IO/BitstreamReader.h>


struct DeblockingFilterDisplayPreference
{
    bool deblockingDisplayPreferenceCancelFlag = false;
    bool displayPriorToDeblockingPreferredFlag = false;
    bool decFrameBufferingConstraintFlag = false;
    std::uint16_t deblockingDisplayPreferenceRepetitionPeriod = 0;

    DeblockingFilterDisplayPreference() = default;
    explicit DeblockingFilterDisplayPreference(BitstreamReader& reader)
    {
        deblockingDisplayPreferenceCancelFlag = reader.readBits<bool, 1>();
        if (!deblockingDisplayPreferenceCancelFlag)
        {
            displayPriorToDeblockingPreferredFlag = reader.readBits<bool, 1>();
            decFrameBufferingConstraintFlag = reader.readBits<bool, 1>();
            deblockingDisplayPreferenceRepetitionPeriod = reader.readExpoGlomb();
        }
    }
};



