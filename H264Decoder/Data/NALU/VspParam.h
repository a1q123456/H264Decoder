#pragma once
#include <IO/BitstreamReader.h>


struct VspParam
{
    struct Value
    {
        std::uint8_t dispartyDiffWji = 0;
        std::uint8_t dispartyDiffOji = 0;
        std::uint8_t dispartyDiffWij = 0;
        std::uint8_t dispartyDiffOij = 0;
    };

    std::vector<std::vector<Value>> values;

    VspParam() = default;
    explicit VspParam(BitstreamReader& reader, int numViews, int predDirection, int index)
    {
        values.resize(numViews);
        for (auto i = 0; i < numViews; i++)
        {
            auto&& vec = values.at(i);
            vec.resize(i);
            for (auto j = 0; j < i; j++)
            {
                vec.at(j).dispartyDiffWji = reader.readExpoGlomb();
                vec.at(j).dispartyDiffOji = reader.readExpoGlomb();
                vec.at(j).dispartyDiffWij = reader.readExpoGlomb();
                vec.at(j).dispartyDiffOij = reader.readExpoGlomb();
            }
        }
    }
};


