#pragma once
#include <IO/BitstreamReader.h>


struct CubemapProjection
{
    bool cmpCancelFlag = false;
    bool cmpPersistenceFlag = false;

    CubemapProjection() = default;
    explicit CubemapProjection(BitstreamReader& reader)
    {
        cmpCancelFlag = reader.readBits<bool, 1>();
        if (!cmpCancelFlag)
        {
            cmpPersistenceFlag = reader.readBits<bool, 1>();
        }
    }
};


