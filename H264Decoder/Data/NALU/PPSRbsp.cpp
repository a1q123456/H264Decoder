#include "PPSRbsp.h"
#include <Data/DecodingContext.h>

PPSRbsp::PPSRbsp(DecodingContext& context, BitstreamReader& reader, NALUnit&)
{
    ppsId = reader.readExpoGlomb();
    spsId = reader.readExpoGlomb();
    entropyCodingModeFlag = reader.readBits<std::uint8_t, 1>();
    bottomFieldPicOrderInFramePresentFlag = reader.readBits<std::uint8_t, 1>();
    numSliceGroupsMinus1 = reader.readExpoGlomb();
    if (numSliceGroupsMinus1 > 0)
    {
        sliceGroupMapType = static_cast<SliceGroupMapType>(reader.readExpoGlomb());
        if (sliceGroupMapType == SliceGroupMapType::Interleaved)
        {
            for (auto iGroup = 0; iGroup <= numSliceGroupsMinus1; iGroup++)
            {
                runLengthMinus1.emplace_back(reader.readExpoGlomb());
            }
        }
        else if (sliceGroupMapType == SliceGroupMapType::ForegroundWithLeftOver)
        {
            for (auto iGroup = 0; iGroup < numSliceGroupsMinus1; iGroup++)
            {
                topLeft.emplace_back(reader.readExpoGlomb());
                bottomRight.emplace_back(reader.readExpoGlomb());
            }
        }
        else if (sliceGroupMapType == SliceGroupMapType::BoxOut ||
            sliceGroupMapType == SliceGroupMapType::RasterScan ||
            sliceGroupMapType == SliceGroupMapType::Wipe)
        {
            sliceGroupChangeDirectionFlag = reader.readBits<std::uint8_t, 1>();
            sliceGroupChangeRateMinus1 = reader.readExpoGlomb();
        }
        else if (sliceGroupMapType == SliceGroupMapType::Explicit)
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
            for (auto i = 0; i < 6 + ((context.currentSPS().chromaFormatIdc != 3) ? 2 : 6) * transform8x8ModeFlag; i++)
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


    if (numSliceGroupsMinus1 == 0)
    {
        mapUnitToSliceGroupMap.clear();
    }
    else
    {
        switch (sliceGroupMapType)
        {
        case SliceGroupMapType::Interleaved:
            mapUnitToSliceGroupMap = getInterleavedGroupMapType(context);
            break;
        case SliceGroupMapType::Dispersed:
            mapUnitToSliceGroupMap = getDispersedGroupMapType(context);
            break;
        case SliceGroupMapType::ForegroundWithLeftOver:
            mapUnitToSliceGroupMap = getForegroundWithLeftOverGroupMapType(context);
            break;
        case SliceGroupMapType::BoxOut:
            mapUnitToSliceGroupMap = getBoxOutMapType(context);
            break;
        case SliceGroupMapType::RasterScan:
            mapUnitToSliceGroupMap = getRasterScanMapType(context);
            break;
        case SliceGroupMapType::Wipe:
            getWipeMapType(context);
            break;
        case SliceGroupMapType::Explicit:
            getExplicitMapType(context);
            break;
        }
    }
}

std::map<int, int> PPSRbsp::getInterleavedGroupMapType(DecodingContext& context)
{

    std::map<int, int> ret;
    auto picSizeInMapUnits = context.getPicSizeInMapUnits();
    auto picWidthInMbs = context.getPicWidthInMbs();

    auto i = 0;
    do
    {
        for (auto iGroup = 0; iGroup <= numSliceGroupsMinus1 && i < picSizeInMapUnits; i += runLengthMinus1[iGroup++] + 1)
        {
            for (auto j = 0; j <= runLengthMinus1[iGroup] && i + j < picSizeInMapUnits; j++)
            {
                ret[i + j] = iGroup;
            }
        }
    } while (i < picSizeInMapUnits);
    return ret;
}

std::map<int, int> PPSRbsp::getDispersedGroupMapType(DecodingContext& context)
{
    std::map<int, int> ret;
    auto picSizeInMapUnits = context.getPicSizeInMapUnits();
    auto picWidthInMbs = context.getPicWidthInMbs();

    for (auto i = 0; i < picSizeInMapUnits; i++)
    {
        ret[i] = ((i % picWidthInMbs) +
            (((i / picWidthInMbs) * (numSliceGroupsMinus1 + 1)) / 2))
            % (numSliceGroupsMinus1 + 1);
    }
    return ret;
}

std::map<int, int> PPSRbsp::getForegroundWithLeftOverGroupMapType(DecodingContext& context)
{
    std::map<int, int> ret;
    auto picSizeInMapUnits = context.getPicSizeInMapUnits();
    auto picWidthInMbs = context.getPicWidthInMbs();

    for (auto i = 0; i < picSizeInMapUnits; i++)
        ret[i] = numSliceGroupsMinus1;


    for (auto iGroup = numSliceGroupsMinus1 - 1; iGroup >= 0; iGroup--)
    {
        auto yTopLeft = topLeft[iGroup] / picWidthInMbs;
        auto xTopLeft = topLeft[iGroup] % picWidthInMbs;
        auto yBottomRight = bottomRight[iGroup] / picWidthInMbs;
        auto xBottomRight = bottomRight[iGroup] % picWidthInMbs;
        for (auto y = yTopLeft; y <= yBottomRight; y++)
            for (auto x = xTopLeft; x <= xBottomRight; x++)
                ret[y * picWidthInMbs + x] = iGroup;
    }

    return ret;
}

std::map<int, int> PPSRbsp::getBoxOutMapType(DecodingContext& context)
{
    std::map<int, int> ret;
    auto picSizeInMapUnits = context.getPicSizeInMapUnits();
    auto picWidthInMbs = context.getPicWidthInMbs();
    auto picHeightInMapUnits = context.getPicHeightInMapUnits();

    for (auto i = 0; i < picSizeInMapUnits; i++)
    {
        ret[i] = 1;
    }

    auto x = (picWidthInMbs - sliceGroupChangeDirectionFlag) / 2;
    auto y = (picHeightInMapUnits - sliceGroupChangeDirectionFlag) / 2;

    auto leftBound = x;
    auto topBound = y;
    auto rightBound = x;
    auto bottomBound = y;
    auto xDir = sliceGroupChangeDirectionFlag - 1;
    auto yDir = (int)(sliceGroupChangeDirectionFlag);

    auto sliceGroupChangeCycle = 0;
    context.getSliceHeader([&](auto&& sliceHeader)
        {
            sliceGroupChangeCycle = sliceHeader.sliceGroupChangeCycle;
        });
    
    auto mapUnitsInSliceGroup0 = context.getMapUnitsInSliceGroup0(sliceGroupChangeRateMinus1);
    int mapUnitVacant = 0;

    for (auto k = 0; k < mapUnitsInSliceGroup0; k += mapUnitVacant) {
        mapUnitVacant = (ret[y * picWidthInMbs + x] == 1);
        if (mapUnitVacant)
            ret[y * picWidthInMbs + x] = 0 (8 - 20);
        if (xDir == -1 && x == leftBound) {
            leftBound = std::max(leftBound - 1, 0);
            x = leftBound;
            xDir = 0;
            yDir = 2 * sliceGroupChangeDirectionFlag - 1;
        }
        else if (xDir == 1 && x == rightBound) {
            rightBound = std::min(rightBound + 1, picWidthInMbs - 1);
            x = rightBound;
            xDir = 0;
            yDir = 1 - 2 * sliceGroupChangeDirectionFlag;
        }
        else if (yDir == -1 && y == topBound) {
            topBound = std::max(topBound - 1, 0);
            y = topBound;
            xDir = 1 - 2 * sliceGroupChangeDirectionFlag;
            yDir = 0;
        }
        else if (yDir == 1 && y == bottomBound) {
            bottomBound = std::min(bottomBound + 1, picHeightInMapUnits - 1);
            y = bottomBound;
            xDir = 2 * sliceGroupChangeDirectionFlag - 1;
            yDir = 0;
        }
        else
        {
            x = x + xDir;
            y = y + yDir;
        }
            
    }
    return ret;
}

std::map<int, int> PPSRbsp::getRasterScanMapType(DecodingContext& context)
{
    std::map<int, int> ret;
    auto picSizeInMapUnits = context.getPicSizeInMapUnits();
    auto picWidthInMbs = context.getPicWidthInMbs();

    auto mapUnitsInSliceGroup0 = context.getMapUnitsInSliceGroup0(sliceGroupChangeRateMinus1);
    auto sizeOfUpperLeftGroup = context.getSizeOfUpperLeftGroup(sliceGroupChangeDirectionFlag, sliceGroupChangeRateMinus1);

    for (auto i = 0; i < picSizeInMapUnits; i++)
        if (i < sizeOfUpperLeftGroup)
            ret[i] = sliceGroupChangeDirectionFlag;
        else
            ret[i] = 1 - sliceGroupChangeDirectionFlag;

    return ret;
}

std::map<int, int> PPSRbsp::getWipeMapType(DecodingContext& context)
{
    std::map<int, int> ret;
    auto picSizeInMapUnits = context.getPicSizeInMapUnits();
    auto picWidthInMbs = context.getPicWidthInMbs();
    auto picHeightInMapUnits = context.getPicHeightInMapUnits();

    auto sizeOfUpperLeftGroup = context.getSizeOfUpperLeftGroup(sliceGroupChangeDirectionFlag, sliceGroupChangeRateMinus1);

    auto k = 0;
    for (auto j = 0; j < picWidthInMbs; j++)
        for (auto i = 0; i < picHeightInMapUnits; i++)
            if (k++ < sizeOfUpperLeftGroup)
                ret[i * picWidthInMbs + j] = sliceGroupChangeDirectionFlag;
            else
                ret[i * picWidthInMbs + j] = 1 - sliceGroupChangeDirectionFlag;

    return ret;
}

std::map<int, int> PPSRbsp::getExplicitMapType(DecodingContext& context)
{
    std::map<int, int> ret;
    auto picSizeInMapUnits = context.getPicSizeInMapUnits();
    auto picWidthInMbs = context.getPicWidthInMbs();
    auto picHeightInMapUnits = context.getPicHeightInMapUnits();

    for (auto i = 0; i <= picSizeInMapUnits - 1; i++)
    {
        ret[i] = sliceGroupId[i];
    }

}
