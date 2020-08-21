#pragma once
#include <IO/BitstreamReader.h>

struct MvcdViewScalabilityInfo
{
    std::uint16_t numOperationPointsMinus1 = 0;
    std::vector<OperationPoint> operationPoints;

    MvcdViewScalabilityInfo() = default;
    explicit MvcdViewScalabilityInfo(BitstreamReader& reader)
    {
        numOperationPointsMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= numOperationPointsMinus1; i++)
        {
            operationPoints.emplace_back(reader, true);
        }
    }
};

