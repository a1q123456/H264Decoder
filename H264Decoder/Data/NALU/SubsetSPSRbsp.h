#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\SeqParameterSetSvcExtension.h>
#include <Data\NALU\SpsMvcExtension.h>
#include <Data\NALU\SvcVuiParametersExtension.h>
#include <Data\NALU\MvcVuiParametersExtension.h>
#include <Data\NALU\SpsMvcdExtension.h>
#include <Data\NALU\Sps3DavcExtension.h>


struct SubsetSPSRbsp
{
    SPSData spsData;
    SeqParameterSetSvcExtension spsSvcExtension;
    bool svcVuiParametersPresentFlag = false;
    SvcVuiParametersExtension svcVuiParametersExtension;
    SpsMvcExtension seqParameterSetMVCExtension;
    MvcVuiParametersExtension mvcVuiParametersExtension;
    SpsMvcdExtension spsMvcdExtension;
    Sps3DavcExtension sps3davcExtension;

    bool mvcVuiParametersPresentFlag = false;
    bool additionalExtension2Flag = false;
    std::vector<BoolType> additionalExtension2DataFlags;
    RbspTrailingBits rbspTrailingBits;

    explicit SubsetSPSRbsp(DecodingContext context, BitstreamReader& reader);

};


