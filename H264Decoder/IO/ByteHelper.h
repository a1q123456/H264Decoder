#pragma once

inline std::unique_ptr<Byte[]> GetBuffer(std::size_t size)
{
    std::unique_ptr<Byte[]> ret(new Byte[size]);
    return ret;
}



