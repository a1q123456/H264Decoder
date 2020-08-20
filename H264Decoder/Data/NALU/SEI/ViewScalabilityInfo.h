#pragma once
#include <IO/BitstreamReader.h>

struct ViewScalabilityInfo
{
    std::uint32_t numOperationPointsMinus1 = 0;
    std::vector<OperationPoint> operationPoints;

    ViewScalabilityInfo() = default;
    explicit ViewScalabilityInfo(BitstreamReader& reader)
    {
        numOperationPointsMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= numOperationPointsMinus1; i++)
        {
            operationPoints.emplace_back(reader, false);
        }
    }
};

