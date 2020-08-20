#pragma once
#include <IO/BitstreamReader.h>


struct OperationPointsNotPresent
{
    std::uint32_t numOperationPoints = 0;
    std::vector<std::uint32_t> operationPointNotPresentId;

    OperationPointsNotPresent() = default;
    explicit OperationPointsNotPresent(BitstreamReader& reader)
    {
        numOperationPoints = reader.readExpoGlomb();
        for (auto i = 0; i <= numOperationPoints; i++)
        {
            operationPointNotPresentId.emplace_back(reader.readExpoGlomb());
        }
    }
};


