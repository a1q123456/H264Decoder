#pragma once
#include <IO/BitstreamReader.h>

enum class SliceType;

template<size_t prefix, size_t suffix>
struct PrefixAndSuffix { };

struct UEG3 {};

class ArithmeticDecodingEngine
{
public:
    ArithmeticDecodingEngine(BitstreamReader& reader)
    {
        codIOffset = reader.readBits<int, 9>();
    }

private:
    int codIRange = 510;
    int codIOffset;
};

class CabacDecoder
{
public:
    CabacDecoder(int picInitQpMinus26, int sliceQpDelta, int cabacInitIdc, SliceType type);

    void ResetAde()
    {
        ade.reset();
    }

    template<typename ...BinarizationMethods>
    void Binarization()
    {

    }

    template<typename ...BinarizationMethods>
    int Decode(BitstreamReader& reader, AeV<BinarizationMethods...>& field)
    {
        if (!ade)
        {
            ade.reset(ArithmeticDecodingEngine{ reader });
        }
        Binarization<BinarizationMethods...>()
    }
private:

    struct CabacContext
    {
        int pStateIdx = 0;
        int valMPS = 0;

        CabacContext(int picInitQpMinus26, int sliceQpDelta, int m, int n);
    };

    std::unordered_map<int, CabacContext> contexts;
    
    std::unique_ptr<ArithmeticDecodingEngine> ade;
};

