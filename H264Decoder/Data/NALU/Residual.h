#pragma once
#include <IO/BitstreamReader.h>
#include <Data/NALU/ResidualBlockCavlc.h>
#include <Data/NALU/ResidualBlockCabac.h>


struct Residual
{
    ResidualBlockCavlc intra16x16DCResidualBlockCavlc;
    ResidualBlockCavlc intra16x16ACResidualBlockCavlc;
    ResidualBlockCavlc lumaResidualBlockCavlc;
    ResidualBlockCavlc chromaDCResidualBlockCavlc;
    ResidualBlockCavlc chromaACResidualBlockCavlc;

    ResidualBlockCabac intra16x16DCResidualBlockCabac;
    ResidualBlockCabac intra16x16ACResidualBlockCabac;
    ResidualBlockCabac lumaResidualBlockCabac;
    ResidualBlockCabac chromaDCResidualBlockCabac;
    ResidualBlockCabac chromaACResidualBlockCabac;
};



