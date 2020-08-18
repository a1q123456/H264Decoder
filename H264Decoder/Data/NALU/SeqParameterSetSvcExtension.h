#pragma once
#include <IO/BitstreamReader.h>


struct SeqParameterSetSvcExtension
{
    bool interLayerDeblockingFilterControlPresentFlag = false;
    std::uint8_t extendedSpatialScalabilityIdc = 0;
    bool chromaPhaseXPlus1Flag = false;
    std::uint8_t chromaPhaseYPlus1 = 0;
    bool seqRefLayerChromaPhaseXPlus1Flag = false;
    std::uint8_t seqRefLayerChromaPhaseYPlus1 = 0;
    std::int8_t seqScaledRefLayerLeftOffset;
    std::int8_t seqScaledRefLayerTopOffset;
    std::int8_t seqScaledRefLayerRightOffset;
    std::int8_t seqScaledRefLayerBottomOffset;
    bool seqTcoeffLevelPredictionFlag = false;
    bool adaptiveTcoeffLevelPredictionFlag = false;
    bool sliceHeaderRestrictionFlag = false;

    SeqParameterSetSvcExtension() = default;
    explicit SeqParameterSetSvcExtension(BitstreamReader& reader, int chromaArrayType)
    {
        interLayerDeblockingFilterControlPresentFlag = reader.readBits<std::uint8_t, 1>();
        extendedSpatialScalabilityIdc = reader.readBits<std::uint8_t, 2>();
        if (chromaArrayType == 1 || chromaArrayType == 2)
        {
            chromaPhaseXPlus1Flag = reader.readBits<std::uint8_t, 1>();
        }
        if (chromaArrayType == 1)
        {
            chromaPhaseYPlus1 = reader.readBits<std::uint8_t, 2>();
        }
        if (extendedSpatialScalabilityIdc == 1)
        {
            if (chromaArrayType > 0)
            {
                seqRefLayerChromaPhaseXPlus1Flag = reader.readBits<std::uint8_t, 1>();
                seqRefLayerChromaPhaseYPlus1 = reader.readBits<std::uint8_t, 2>();
            }
            seqScaledRefLayerLeftOffset = reader.readSignedExpoGlomb();
            seqScaledRefLayerTopOffset = reader.readSignedExpoGlomb();
            seqScaledRefLayerRightOffset = reader.readSignedExpoGlomb();
            seqScaledRefLayerBottomOffset = reader.readSignedExpoGlomb();
        }
        seqTcoeffLevelPredictionFlag = reader.readBits<std::uint8_t, 1>();
        adaptiveTcoeffLevelPredictionFlag = reader.readBits<std::uint8_t, 1>();
        sliceHeaderRestrictionFlag = reader.readBits<std::uint8_t, 1>();

    }

};

