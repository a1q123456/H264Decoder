#pragma once
#include <IO/BitstreamReader.h>

enum class SliceType;

template<size_t prefix, size_t suffix>
struct PrefixAndSuffix { };

struct UEG3 {};

class CabacDecoder
{
public:
    CabacDecoder(int picInitQpMinus26, int sliceQpDelta, int cabacInitIdc, SliceType type);

    template<typename ...BinarizationMethods>
    int Decode(BitstreamReader& reader, AeV<BinarizationMethods...>& field)
    {

    }
private:

    struct CabacContext
    {
        int pStateIdx = 0;
        int valMPS = 0;

        CabacContext(int picInitQpMinus26, int sliceQpDelta, int m, int n);
    };

    std::unordered_map<int, CabacContext> contexts;
};

