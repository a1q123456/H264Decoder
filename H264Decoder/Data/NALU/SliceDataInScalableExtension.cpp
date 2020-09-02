#include "pch.h"
#include "SliceDataInScalableExtension.h"
#include <Data/DecodingContext.h>
#include <Data\NALU\SliceHeaderInScalableExtension.h>


SliceDataInScalableExtension::SliceDataInScalableExtension(DecodingContext& context, BitstreamReader& reader)
{
    auto entropyCodingModeFlag = context.currentPPS().entropyCodingModeFlag;
    if (!entropyCodingModeFlag)
    {
        while (!reader.byteAligned())
        {
            cabacAlignmentOneBit.emplace_back(reader.readBits<std::uint8_t, 1>());
        }
        std::uint64_t firstMbInSlice = 0;
        SliceType sliceType;

        context.getSliceHeader([&](auto header)
            {
                firstMbInSlice = header.firstMbInSlice;
                sliceType = header.sliceType;
            });
        auto mbaffFrameFlag = context.getMbaffFrameFlag();
        auto curMbAddr = firstMbInSlice * (1 + (mbaffFrameFlag ? 1 : 0));
        auto moreDataFlag = true;
        auto prevMbSkipped = false;

        do
        {
            SliceDataInScalableExtensionData data;

            if (sliceType != SliceType::EI)
            {
                if (!entropyCodingModeFlag)
                {
                    data.mbSkipRun = reader.readExpoGlomb();
                    prevMbSkipped = data.mbSkipRun > 0;
                    for (auto i = 0; i < data.mbSkipRun; i++)
                    {
                        curMbAddr = context.nextMbAddress(curMbAddr);
                    }
                    if (data.mbSkipRun > 0)
                    {
                        moreDataFlag = reader.moreRbspData();
                    }
                }
                else
                {
                    data.mbSkipFlag = reader.readAeV();
                    moreDataFlag = !data.mbSkipFlag;
                }
            }
            if (moreDataFlag)
            {
                if (mbaffFrameFlag && ((curMbAddr % 2) == 0 || ((curMbAddr % 2) == 1 && prevMbSkipped)))
                {
                    data.mbFieldDecodingFlag = reader.readAeV();
                }
                data.macroBlockLayerInScalableExtension = MacroBlockLayerInScalableExtension{ reader };
            }
            if (!entropyCodingModeFlag)
            {
                moreDataFlag = reader.moreRbspData();
            }
            else
            {
                if (sliceType != SliceType::EI)
                {
                    prevMbSkipped = data.mbSkipFlag;
                }
                if (mbaffFrameFlag && (curMbAddr % 2) == 0)
                {
                    moreDataFlag = true;
                }
                else
                {
                    data.endOfSliceFlag = reader.readAeV();
                    moreDataFlag = !data.endOfSliceFlag;
                }
            }
            curMbAddr = context.nextMbAddress(curMbAddr);

        } while (moreDataFlag);
    }
}
