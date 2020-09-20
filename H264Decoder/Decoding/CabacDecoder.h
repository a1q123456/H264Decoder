#pragma once

enum class SliceType;
class BitstreamReader;

class CabacDecoder
{
public:
    CabacDecoder(int picInitQpMinus26, int sliceQpDelta, int cabacInitIdc, SliceType type);
    int Decode(BitstreamReader& reader);
private:

    struct CabacContext
    {
        int pStateIdx = 0;
        int valMPS = 0;

        CabacContext(int picInitQpMinus26, int sliceQpDelta, int m, int n);
    };

    std::unordered_map<int, CabacContext> contexts;
};

