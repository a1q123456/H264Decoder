#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\SEI\OperationPoint.h>

struct ViewScalabilityInfo
{
    std::uint16_t numOperationPointsMinus1 = 0;
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

