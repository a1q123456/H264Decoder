#pragma once
#include <IO/BitstreamReader.h>

struct SparePic
{
    struct Data
    {
        std::uint16_t deltaSpareFrameNum = 0;
        bool spareBottomFieldFlag = false;
        std::uint16_t spareAreaIdc = 0;
        std::vector<BoolType> spareUnitFlag;

        std::vector<std::uint16_t> zeroRunLength;
    };

    std::uint16_t targetFrameNum = 0;
    bool spareFieldFlag = false;
    bool targetBottomFieldFlag = false;
    std::uint16_t numSparePicMinus1 = 0;

    SparePic() = default;
    explicit SparePic(DecodingContext& ctx, BitstreamReader& reader)
    {
        targetFrameNum = reader.readExpoGlomb();
        spareFieldFlag = reader.readBits<bool, 1>();
        if (spareFieldFlag)
        {
            targetBottomFieldFlag = reader.readBits<bool, 1>();
        }
        numSparePicMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i < numSparePicMinus1 + 1; i++)
        {
            Data data;
            data.deltaSpareFrameNum = reader.readExpoGlomb();
            if (spareFieldFlag)
            {
                data.spareBottomFieldFlag = reader.readBits<bool, 1>();
            }
            data.spareAreaIdc = reader.readExpoGlomb();
            if (data.spareAreaIdc == 1)
            {
                for (auto j = 0; j < ctx.getPicSizeInMapUnits(); j++)
                {
                    data.spareUnitFlag.emplace_back(reader.readBits<bool, 1>());
                }
            }
            else if (data.spareAreaIdc == 2)
            {
                auto mapUnitCnt = 0;
                for (auto j = 0; mapUnitCnt < ctx.getPicSizeInMapUnits(); j++)
                {
                    mapUnitCnt += (data.zeroRunLength.emplace_back(reader.readExpoGlomb()) + 1);
                }
            }
        }
    }
};


