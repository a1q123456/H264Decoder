#include "pch.h"
#include <H264Decoder/Data/NALUnit.h>
#include <H264Decoder/IO/BitstreamReader.h>
#include <H264Decoder/IO/NALUnitReader.h>
#include <H264Decoder/Data/DecodingContext.h>

int main()
{
    ByteFileFstream reader;
    reader.exceptions(ByteFileFstream::failbit | ByteFileFstream::badbit);
    reader.open("D:\\ys.264", std::ios_base::in | std::ios_base::binary);
    DecodingContext context;
    NALUnitReader br(context, reader, true);
    NALUnit nalu;
    while (true)
    {
        if (!br.readNALUnit(nalu))
        {
            auto a = nalu.rbsp;
        }
    }
    

    return 0;
}
