#pragma once
#include <Data/Byte.h>

using ByteStream = std::basic_iostream<Byte>;
using ByteFileFstream = std::basic_fstream<Byte>;
using BoolType = std::uint8_t;

template<typename ...BinarizationMethods>
struct AeV
{
    using Type = int;

    Type val;
    AeV() = default;
    AeV(int v) : val(v) {}
};

using CeV = std::uint8_t;

class BitstreamReader
{
public:
    explicit BitstreamReader(ByteStream& bs) : bs(&bs)
    {

    }

    explicit BitstreamReader(std::vector<Byte>&& data) : underlying(std::move(data))
    {

    }

    std::size_t totalSize()
    {
        return underlying.size();
    }

    void advancePos(int n);

    template<typename T, size_t N>
    T nextBits()
    {
        static_assert(((std::uint64_t(1) << N) - 1) <= std::numeric_limits<T>::max());
        backupByteBuffer = byteBuffer;
        backupPos = pos;
        backupNextBitsBufferIndex = nextBitsBufferIndex;
        std::uint64_t ret;
        try
        {
            ret = internalReadBits(N, true, false);
        }
        catch (...)
        {
            byteBuffer = backupByteBuffer;
            pos = backupPos;
            nextBitsBufferIndex = backupNextBitsBufferIndex;
            throw;
        }
        byteBuffer = backupByteBuffer;
        pos = backupPos;
        nextBitsBufferIndex = backupNextBitsBufferIndex;
        

        return static_cast<T>(ret);
    }

    bool byteAligned()
    {
        return pos % 8 == 0;
    }

    template<typename T>
    T readBits(int n)
    {
        assert(static_cast<std::uint64_t>((1 << n) - 1) <= std::numeric_limits<T>::max());
        return static_cast<T>(internalReadBits(n, false, false));
    }

    template<typename T, size_t N>
    T readBits()
    {
        static_assert(N <= 64);
        if constexpr (!std::is_same_v<T, bool>)
        {
            if constexpr (std::is_signed_v<T>)
            {
                static_assert(((std::uint64_t(1) << (N / 2)) - 1) <= std::numeric_limits<T>::max());
            }
            else
            {
                static_assert(((std::uint64_t(1) << N) - 1) <= std::numeric_limits<T>::max());
            }
            
        }
        else
        {
            static_assert(N == 1);
        }
        return static_cast<T>(internalReadBits(N, false, false));
    }
    
    std::uint16_t readExpoGlomb();
    std::int16_t readSignedExpoGlomb();

    bool moreRbspData();

    bool moreData() const noexcept;

private:
    std::uint8_t probeLeadingZeros();
    std::uint64_t internalReadBits(int n, bool isNext, bool continueNext);

private:
    std::vector<std::uint8_t> nextBitsBuffer;
    std::size_t nextBitsBufferIndex = 0;
    std::uint8_t backupByteBuffer = 0;
    std::uint8_t backupPos = 0;
    std::size_t backupNextBitsBufferIndex = 0;


    std::vector<Byte> underlying;
    std::size_t index = 0;
    std::int8_t pos = 8;
    std::uint8_t byteBuffer = 0;

    ByteStream* bs = nullptr;

};


