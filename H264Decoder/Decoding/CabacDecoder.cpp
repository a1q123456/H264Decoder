#include "pch.h"
#include "CabacDecoder.h"
#include "CabacTable.h"

void CabacDecoder::InitializeContextVariables(int picInitQpMinus26, int sliceQpDelta)
{


}

inline void CabacDecoder::CabacContext::InitVariables(int picInitQpMinus26, int sliceQpDelta, int m, int n)
{

    auto SliceQPy = 26 + picInitQpMinus26 + sliceQpDelta;

    auto preCtxState = std::clamp(((m * std::clamp(SliceQPy, 0, 51)) >> 4) + n, 1, 126);
    if (preCtxState <= 63) {
        pStateIdx = 63 - preCtxState;
        valMPS = 0;
    }
    else {
        pStateIdx = preCtxState - 64;
        valMPS = 1;
    }
}
