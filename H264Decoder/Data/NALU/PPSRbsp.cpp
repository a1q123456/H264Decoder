#include "PPSRbsp.h"
#include <Data/DecodingContext.h>

PPSRbsp::PPSRbsp(DecodingContext& context, BitstreamReader& reader)
{
    ppsId = reader.readExpoGlomb();
    spsId = reader.readExpoGlomb();
    entropyCodingModeFlag = reader.readBits<std::uint8_t, 1>();
    bottomFieldPicOrderInFramePresentFlag = reader.readBits<std::uint8_t, 1>();
    numSliceGroupsMinus1 = reader.readExpoGlomb();
    if (numSliceGroupsMinus1 > 0)
    {
        sliceGroupMapType = reader.readExpoGlomb();
        if (sliceGroupMapType == 0)
        {
            for (auto iGroup = 0; iGroup <= numSliceGroupsMinus1; iGroup++)
            {
                runLengthMinus1.emplace_back(reader.readExpoGlomb());
            }
        }
        else if (sliceGroupMapType == 2)
        {
            for (auto iGroup = 0; iGroup < numSliceGroupsMinus1; iGroup++)
            {
                topLeft.emplace_back(reader.readExpoGlomb());
                bottomRight.emplace_back(reader.readExpoGlomb());
            }
        }
        else if (sliceGroupMapType == 3 ||
            sliceGroupMapType == 4 ||
            sliceGroupMapType == 5)
        {
            sliceGroupChangeDirectionFlag = reader.readBits<std::uint8_t, 1>();
            sliceGroupChangeRateMinus1 = reader.readExpoGlomb();
        }
        else if (sliceGroupMapType == 6)
        {
            picSizeInMapUnitsMinus1 = reader.readExpoGlomb();
            for (auto i = 0; i <= picSizeInMapUnitsMinus1; i++)
            {
                sliceGroupId.emplace_back(reader.readBits<std::uint16_t>(static_cast<int>(std::ceil(std::log2(numSliceGroupsMinus1 + 1)))));
            }
        }
    }
    numRefIdxl0DefaultActiveMinus1 = reader.readExpoGlomb();
    numRefIdxl1DefaultActiveMinus1 = reader.readExpoGlomb();
    weightedPredFlag = reader.readBits<std::uint8_t, 1>();
    weightedBipredIdc = reader.readBits<std::uint8_t, 2>();
    picInitQPMinus26 = reader.readSignedExpoGlomb();
    picInitQSMinus26 = reader.readSignedExpoGlomb();
    chromaQPIndexOffset = reader.readSignedExpoGlomb();

    deblockingFilterControlPresentFlag = reader.readBits<std::uint8_t, 1>();
    constraintedIntraPredFlag = reader.readBits<std::uint8_t, 1>();
    redundantPicCntPresentFlag = reader.readBits<std::uint8_t, 1>();
    if (reader.moreData())
    {
        transform8x8ModeFlag = reader.readBits<std::uint8_t, 1>();
        picScalingMatrixPresentFlag = reader.readBits<std::uint8_t, 1>();

        if (picScalingMatrixPresentFlag)
        {
            for (auto i = 0; i < 6 + ((context.currentSPS().spsData.chromaFormatIdc != 3) ? 2 : 6) * transform8x8ModeFlag; i++)
            {
                auto&& list = i < 6 ? scalingList4x4.emplace_back() : scalingList8x8.emplace_back();
                auto present = reader.readBits<std::uint8_t, 1>();
                if (present)
                {
                    list.scalingList.resize(i < 6 ? 16 : 64);
                    readScalingList(reader, list.scalingList, list.scalingList.size(), list.useDefaultFlag);
                }
            }
        }
        secondChromaQPIndexOffset = reader.readSignedExpoGlomb();
    }

    rbspTrailingBits = RbspTrailingBits{ reader };
    context.addPPS(*this);
}
