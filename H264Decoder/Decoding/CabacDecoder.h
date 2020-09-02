#pragma once

class CabacDecoder
{
public:
    void InitializeContextVariables(int picInitQpMinus26, int sliceQpDelta);

private:
    int pStateIdx = 0;
    int valMPS = 0;
    int ctxIdx = 0;
};

