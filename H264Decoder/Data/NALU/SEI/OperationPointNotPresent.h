#pragma once
#include <IO/BitstreamReader.h>


struct OperationPointNotPresent
{
    std::uint32_t numOperationPoints = 0;
    std::vector<std::uint32_t> operationPointNotPresentId;

    OperationPointNotPresent() = default;
    explicit OperationPointNotPresent(BitstreamReader& reader)
    {
        numOperationPoints = reader.readExpoGlomb();
        for (auto k = 0; k < numOperationPoints; k++)
        {
            operationPointNotPresentId.emplace_back(reader.readExpoGlomb());
        }
    }
};

