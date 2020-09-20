#include "pch.h"
#include "CabacDecoder.h"
#include "CabacTable.h"

CabacDecoder::CabacDecoder(int picInitQpMinus26, int sliceQpDelta, int cabacInitIdc, SliceType type)
{
    for (auto ctxIdx = 0; ctxIdx < 1024; ctxIdx++)
    {
        auto mnValues = CabacTables::mnValues[ctxIdx][cabacInitIdc][static_cast<int>(type) % 3];
        contexts[ctxIdx] = CabacContext{
            picInitQpMinus26,
            sliceQpDelta,
            mnValues[0],
            mnValues[1]
        };
    }

}

int CabacDecoder::Decode(BitstreamReader& reader)
{

}

CabacDecoder::CabacContext::CabacContext(int picInitQpMinus26, int sliceQpDelta, int m, int n)
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
