#include "SPSRbsp.h"
#include <Data\DecodingContext.h>


SPSRbsp::SPSRbsp(DecodingContext& context, BitstreamReader& reader)
{
    spsData = SPSData{ reader };
    rbspTrailingBits = RbspTrailingBits{ reader };
    context.addSPS(*this);
}
