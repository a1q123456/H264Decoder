#pragma once

constexpr int mValues0_10[]
{
    20, 2, 3, 20, 2, 3, -28, -23, -6, -1, 7,
};

constexpr int mValues11_23[][13]
{
    {23, 23, 21, 1, 0, -37, 5, -13, -11, 1, 12, -4, 17},
    {22, 34, 16, -2, 4, -29, 2, -6, -13, 5, 9, -3, 10},
    {29, 25, 14, -10, -3, -27, 26, -4, -24, 5, 6, -17, 14}
};

constexpr int mValues24_39[][16]
{
    {18, 9, 29, 26, 16, 9, -46, -20, 1, -13, -11, 1, -6, -17, -6, 9},
    {26, 19, 40, 57, 41, 26, -45, -15, -4, -6, -13, 5, 6, -13, 0, 8},
    {20, 20, 29, 54, 37, 12, -32, -22, -2, -4, -24, 5, -6, -14, -6, 4}
};

constexpr int mValues40_53[][14]
{
    {-3, -6, -11, 6, 7, -5, 2, 0, -3, -10, 5, 4, -3, 0},
    {-2, -5, -10, 2, 2, -3, -3, 1, -3, -6, 0, -3, -7, -5},
    {-11, -15, -21, 19, 20, 4, 6, 1, -5, -13, 5, 6, -3, -1}
};

class CabacDecoder
{
public:
    void InitializeContextVariables(int picInitQpMinus26, int sliceQpDelta);

private:

    struct CabacContext
    {
        int pStateIdx = 0;
        int valMPS = 0;
        int ctxIdx = 0;

        void InitVariables(int picInitQpMinus26, int sliceQpDelta, int m, int n);
    };

};

