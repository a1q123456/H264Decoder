#pragma once
#include <IO/BitstreamReader.h>


struct RedundantPicProperty
{
    struct DId
    {
        struct QId
        {
            struct RedundantPic
            {
                std::uint32_t redundantPicCntMinus1 = 0;
                bool picMatchFlag = false;

                bool mbTypeMatchFlag = false;
                bool motionMatchFlag = false;
                bool residualMatchFlag = false;
                bool intraSamplesMatchFlag = false;

                RedundantPic() = default;
                explicit RedundantPic(BitstreamReader& reader)
                {
                    redundantPicCntMinus1 = reader.readExpoGlomb();
                    picMatchFlag = reader.readBits<bool, 1>();
                    if (!picMatchFlag)
                    {
                        mbTypeMatchFlag = reader.readBits<bool, 1>();
                        motionMatchFlag = reader.readBits<bool, 1>();
                        residualMatchFlag = reader.readBits<bool, 1>();
                        intraSamplesMatchFlag = reader.readBits<bool, 1>();
                    }
                }
            };

            std::uint8_t qualityId = 0;
            std::uint16_t numRedundantPicsMinus1 = 0;
            std::vector<RedundantPic> redundantPics;

            QId() = default;
            explicit QId(BitstreamReader& reader)
            {
                qualityId = reader.readBits<std::uint8_t, 4>();
                numRedundantPicsMinus1 = reader.readExpoGlomb();
                for (auto k = 0; k <= numRedundantPicsMinus1; k++)
                {
                    redundantPics.emplace_back(reader);
                }

            }
        };

        std::uint8_t dependencyId = 0;
        std::uint16_t numQIdsMinus1 = 0;
        std::vector<QId> qIds;

        DId() = default;
        explicit DId(BitstreamReader& reader)
        {
            dependencyId = reader.readBits<std::uint8_t, 3>();
            numQIdsMinus1 = reader.readExpoGlomb();
            for (auto j = 0; j <= numQIdsMinus1; j++)
            {
                qIds.emplace_back(reader);
            }
        }
    };

    std::uint16_t numDIdsMinus1 = 0;
    std::vector<DId> dIds;

    RedundantPicProperty() = default;
    explicit RedundantPicProperty(BitstreamReader& reader)
    {
        numDIdsMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= numDIdsMinus1; i++)
        {
            dIds.emplace_back(reader);
        }
    }
};

