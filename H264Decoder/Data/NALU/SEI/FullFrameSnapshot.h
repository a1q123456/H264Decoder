#pragma once
#include <IO/BitstreamReader.h>


struct FullFrameSnapshot
{
    std::uint16_t snapshotId = 0;

    FullFrameSnapshot() = default;
    explicit FullFrameSnapshot(BitstreamReader& reader)
    {
        snapshotId = reader.readExpoGlomb();
    }
};


