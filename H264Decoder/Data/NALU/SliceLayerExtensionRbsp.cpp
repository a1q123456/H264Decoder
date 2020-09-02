#include "pch.h"
#include "SliceLayerExtensionRbsp.h"
#include <Data/NALUnit.h>

inline SliceLayerExtensionRbsp::SliceLayerExtensionRbsp(DecodingContext& context, BitstreamReader& reader, NALUnit& nal)
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
        rbspSliceTrailingBits = RbspSliceTrailingBits{ context, reader };
    }

}
