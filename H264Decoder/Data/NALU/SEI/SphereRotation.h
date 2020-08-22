#pragma once
#include <IO/BitstreamReader.h>


struct SphereRotation
{
    bool sphereRotationCancelFlag = false;
    bool sphereRotationPersistenceFlag = false;
    std::uint8_t sphereRotationReservedZero6Bits = 0;

    std::int32_t yawRotation = 0;
    std::int32_t pitchRotation = 0;
    std::int32_t rollRotation = 0;

    SphereRotation() = default;
    explicit SphereRotation(BitstreamReader& reader)
    {
        sphereRotationCancelFlag = reader.readBits<bool, 1>();
        if (!sphereRotationCancelFlag)
        {
            sphereRotationPersistenceFlag = reader.readBits<bool, 1>();
            sphereRotationReservedZero6Bits = reader.readBits<std::uint8_t, 6>();
            yawRotation = reader.readBits<std::int32_t, 32>();
            pitchRotation = reader.readBits<std::int32_t, 32>();
            rollRotation = reader.readBits<std::int32_t, 32>();
        }
    }
};



