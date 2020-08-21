#pragma once
#include <IO/BitstreamReader.h>


struct FullFrameFreeze
{
    std::uint16_t fullFrameFreezeRepetitionPreiod = 0;

    FullFrameFreeze() = default;
    explicit FullFrameFreeze(BitstreamReader& reader)
    {
        fullFrameFreezeRepetitionPreiod = reader.readExpoGlomb();
    }
};


