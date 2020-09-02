#pragma once
#include <IO/BitstreamReader.h>
#include <Data\NALU\SliceHeaderIn3DAVCExtension.h>
#include <Data\NALU\SliceDataInScalableExtension.h>
#include <Data\NALU\SliceHeaderInScalableExtension.h>
#include <Data\NALU\SliceData.h>
#include <Data\NALU\RbspSliceTrailingBits.h>
#include <Data\NALU\SliceDataIn3DAVCExtension.h>

struct DecodingContext;

struct SliceLayerExtensionRbsp
{
    SliceHeaderInScalableExtension sliceHeaderInScalableExtension;
    SliceDataInScalableExtension sliceDataInScalableExtension;
    SliceHeaderIn3DAVCExtension sliceHeaderIn3DAVCExtension;
    SliceDataIn3DAVCExtension sliceDataIn3DAVCExtension;
    SliceHeader sliceHeader;
    SliceData sliceData;

    RbspSliceTrailingBits rbspSliceTrailingBits;

    SliceLayerExtensionRbsp() = default;
    explicit SliceLayerExtensionRbsp(DecodingContext& context, BitstreamReader& reader, NALUnit& nal)
    {
        if (nal.svcExtensionFlag)
        {
            sliceHeaderInScalableExtension = SliceHeaderInScalableExtension{ context, reader, nal };
            if (!sliceHeaderInScalableExtension.sliceSkipFlag)
            {
                sliceDataInScalableExtension = SliceDataInScalableExtension{ reader };
            }
            
            else if (nal.avc3DExtensionFlag)
            {
                sliceHeaderIn3DAVCExtension = SliceHeaderIn3DAVCExtension{ reader };
                sliceDataIn3DAVCExtension = SliceDataIn3DAVCExtension{ reader };
            }
            else
            {
                sliceHeader = SliceHeader{ reader };
                sliceData = SliceData{ reader };
            }
            rbspSliceTrailingBits = RbspSliceTrailingBits{ reader };
        }
        
    }
};


