#include "BitstreamReader.h"
#include <pch.h>
#include <Data/Byte.h>

void BitstreamReader::advancePos(int n)
{
    internalReadBits(n, false, false);
}

std::uint16_t BitstreamReader::readExpoGlomb()
{
    auto len = probeLeadingZeros();
    auto val = internalReadBits(len + 1, false, false);
    assert(val - 1 <= std::numeric_limits<std::uint16_t>::max());
    return static_cast<std::uint16_t>(val - 1);
}

std::int16_t BitstreamReader::readSignedExpoGlomb()
{
    auto val = readExpoGlomb();
    std::int64_t ret;
    if (val % 2 == 1)
    {
        ret = (val + 1) / 2;
    }
    ret = val / -2;

    assert(ret <= std::numeric_limits<std::int16_t>::max());
    assert(ret >= std::numeric_limits<std::int16_t>::min());
    return static_cast<std::int16_t>(ret);

}

bool BitstreamReader::moreRbspData()
{
    if (!moreData())
    {
        return false;
    }

    if (bs != nullptr)
    {
        throw std::logic_error("not supported");
    }

    if (underlying.empty())
    {
        return false;
    }

    auto lastByte = underlying.back();
    if (lastByte == 0)
    {
        throw std::runtime_error("rbsp_trailing_bits is not found");
    }

    if (index + 1 != underlying.size())
    {
        return true;
    }

    auto lastOnePos = 0;
    for (lastOnePos = 0; lastOnePos < 8; lastOnePos++)
    {
        if ((lastByte & (1 << lastOnePos)) != 0)
        {
            break;
        }
    }
    
    auto nextPos = (pos % 8) + 1;

    if ((8 - lastOnePos) == nextPos)
    {
        return false;
    }
    return true;
}

bool BitstreamReader::moreData() const noexcept
{
    return (!underlying.empty() || !nextBitsBuffer.empty() || pos != 8 || (bs && !bs->eof()));
}

std::uint8_t BitstreamReader::probeLeadingZeros()
{
    std::uint8_t i = 0;
    while (nextBits<std::uint8_t, 1>() == 0)
    {
        i++;
        advancePos(1);
    }
    return i;
}

std::uint64_t BitstreamReader::internalReadBits(int n, bool next, bool continueNext)
{
    if (n == 0)
    {
        return 0;
    }

    std::uint64_t ret = 0;

    if (pos == 8)
    {
        if (nextBitsBufferIndex < nextBitsBuffer.size())
        {
            byteBuffer = static_cast<Byte>(nextBitsBuffer[nextBitsBufferIndex]);
            nextBitsBufferIndex++;
            if (!next && nextBitsBufferIndex == nextBitsBuffer.size())
            {
                nextBitsBuffer.clear();
                nextBitsBufferIndex = 0;
            }
        }
        else if (!underlying.empty())
        {
            assert(index < underlying.size());
            byteBuffer = static_cast<Byte>(underlying[index]);
            index++;
            if (index == underlying.size())
            {
                underlying.clear();
                index = 0;
            }
            if (next)
            {
                nextBitsBuffer.push_back(byteBuffer);
                nextBitsBufferIndex++;
            }
        }
        else if (bs)
        {
            byteBuffer = static_cast<Byte>(bs->get());
            if (next)
            {
                nextBitsBuffer.push_back(byteBuffer);
                nextBitsBufferIndex++;
            }
        }
        else
        {
            throw std::out_of_range("no more data");
        }

        pos = 0;
    }

    auto mask = static_cast<std::uint8_t>(~(static_cast<std::uint8_t>(0xFE) << (7 - pos)));
    auto remain = static_cast<std::uint8_t>(byteBuffer & mask);
    auto remainLen = 8 - pos;
    auto bitsToRead = std::min(remainLen, n);
    auto rShift = remainLen - bitsToRead;
    ret = remain >> rShift;
    pos += bitsToRead;
    n -= bitsToRead;

    if (n > 0)
    {
        assert(pos == 8);

        while (n > 0)
        {
            auto bitsToRead = std::min(8, n);
            auto data = internalReadBits(bitsToRead, next, true);
            n -= bitsToRead;
            ret = ret << bitsToRead;
            ret |= data;
        }

    }

    return ret;

}
