#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\AnchorRef.h>
#include <Data\NALU\SpsMvcLevelValuesSignalled.h>


struct SpsMvcExtension
{
    std::uint8_t numViewsMinus1 = 0;
    std::vector<std::uint8_t> viewId;

    std::vector<AnchorRef> anchorRefs;
    std::vector<AnchorRef> nonAnchorRefs;
    std::uint8_t numLevelValuesSignalledMinus1 = 0;
    std::vector<SpsMvcLevelValuesSignalled> levelValuesSignalled;

    std::uint8_t mfcFormatIdc = 0;
    bool defaultGridPositionFlag = false;
    std::uint8_t view0GridPositionX = 0;
    std::uint8_t view0GridPositionY = 0;
    std::uint8_t view1GridPositionX = 0;
    std::uint8_t view1GridPositionY = 0;

    bool rpuFilterEnabledFlag = false;
    bool rpuFieldProcessingFlag = false;

    SpsMvcExtension() = default;
    explicit SpsMvcExtension(BitstreamReader& reader, int profileIdc)
    {
        numViewsMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= numViewsMinus1; i++)
        {
            viewId.push_back(reader.readExpoGlomb());
        }
        for (auto i = 1; i <= numViewsMinus1; i++)
        {
            anchorRefs.emplace_back(reader);
        }
        for (auto i = 1; i <= numViewsMinus1; i++)
        {
            nonAnchorRefs.emplace_back(reader);
        }
        numLevelValuesSignalledMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i < numLevelValuesSignalledMinus1; i++)
        {
            levelValuesSignalled.emplace_back(reader);
        }
        if (profileIdc == 134)
        {
            mfcFormatIdc = reader.readBits<std::uint8_t, 6>();
            if (mfcFormatIdc == 0 || mfcFormatIdc == 1)
            {
                defaultGridPositionFlag = reader.readBits<std::uint8_t, 1>();
                if (!defaultGridPositionFlag)
                {
                    view0GridPositionX = reader.readBits<std::uint8_t, 4>();
                    view0GridPositionY = reader.readBits<std::uint8_t, 4>();
                    view1GridPositionX = reader.readBits<std::uint8_t, 4>();
                    view1GridPositionY = reader.readBits<std::uint8_t, 4>();
                }
            }
            rpuFilterEnabledFlag = reader.readBits<std::uint8_t, 1>();
            if (!rpuFilterEnabledFlag)
            {
                rpuFieldProcessingFlag = reader.readBits<std::uint8_t, 1>();
            }
        }
    }
};


