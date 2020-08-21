#pragma once
#include <IO/BitstreamReader.h>


struct FramePackingArrangement
{
    std::uint16_t framePackingArrangementId = 0;
    bool framePackingArrangementCancelFlag = false;

    std::uint8_t framePackingArrangementType = 0;
    bool quincunxSamplingFlag = false;
    std::uint8_t contentInterpretationType = 0;
    bool spatialFlippingFlag = false;
    bool frame0FlippedFlag = false;
    bool fieldViewsFlag = false;
    bool currentFrameIsFrame0Flag = false;
    bool frame0SelfContainedFlag = false;
    bool frame1SelfContainedFlag = false;
    std::uint8_t frame0GridPositionX = 0;
    std::uint8_t frame0GridPositionY = 0;
    std::uint8_t frame1GridPositionX = 0;
    std::uint8_t frame1GridPositionY = 0;

    std::uint8_t framePackingArrangementReservedByte = 0;
    std::uint16_t framePackingArrangementRepetitionPeriod = 0;

    bool framePackingArrangementExtensionFlag = false;

    FramePackingArrangement() = default;
    explicit FramePackingArrangement(BitstreamReader& reader)
    {
        framePackingArrangementId = reader.readExpoGlomb();
        framePackingArrangementCancelFlag = reader.readBits<bool, 1>();
        if (!framePackingArrangementCancelFlag)
        {
            framePackingArrangementType = reader.readBits<std::uint8_t, 7>();
            quincunxSamplingFlag = reader.readBits<bool, 1>();
            contentInterpretationType = reader.readBits<std::uint8_t, 6>();
            spatialFlippingFlag = reader.readBits<bool, 1>();
            frame0FlippedFlag = reader.readBits<bool, 1>();
            fieldViewsFlag = reader.readBits<bool, 1>();
            currentFrameIsFrame0Flag = reader.readBits<bool, 1>();
            frame0SelfContainedFlag = reader.readBits<bool, 1>();
            frame1SelfContainedFlag = reader.readBits<bool, 1>();
            if (!quincunxSamplingFlag && framePackingArrangementType != 5)
            {
                frame0GridPositionX = reader.readBits<std::uint8_t, 4>();
                frame0GridPositionY = reader.readBits<std::uint8_t, 4>();
                frame1GridPositionX = reader.readBits<std::uint8_t, 4>();
                frame1GridPositionY = reader.readBits<std::uint8_t, 4>();
            }
            framePackingArrangementReservedByte = reader.readBits<std::uint8_t, 8>();
            framePackingArrangementRepetitionPeriod = reader.readExpoGlomb();
        }
        framePackingArrangementExtensionFlag = reader.readBits<bool, 1>();
    }
};



