#include <gtest/gtest.h>
#include <IO/BitstreamReader.h>


TEST(TestBitstreamReader, TestNextBitsAlignedSingleByte)
{
    std::vector<Byte> data{ 0x40, 0xA0 };
    BitstreamReader br(std::move(data));

    auto b = br.nextBits(3);
    auto b2 = br.readBits(3);

    EXPECT_EQ(b, b2);
    EXPECT_EQ(b, 2);
}

TEST(TestBitstreamReader, TestNextBitsAlignedMultipleByteFromStream)
{
    class MemStreamBuf : public std::basic_streambuf<Byte>
    {
    public:
        MemStreamBuf(std::vector<Byte>&& data) : underlying(std::move(data))
        {
            this->setg(underlying.data(), underlying.data(), underlying.data() + underlying.size());
        }

    private:
        std::vector<Byte> underlying;
    };


    std::vector<Byte> data{ 0x2C, 0xA0, 0x6A, 0x7C };

    MemStreamBuf buf(std::move(data));
    ByteStream ios(&buf);


    BitstreamReader br(ios);

    auto aa = br.nextBits(16);
    auto a = br.nextBits(16);
    auto a2 = br.readBits(8);
    auto b = br.nextBits(16);
    auto b2 = br.readBits(8);

    EXPECT_EQ(a, aa);
    EXPECT_EQ(a, 0x2CA0);
    EXPECT_EQ(a2, 0x2C);
    EXPECT_EQ(b, 0xA06A);
    EXPECT_EQ(b2, 0xA0);
}

TEST(TestBitstreamReader, TestNextBitsAlignedMultipleByte)
{

    std::vector<Byte> data{ 0x2C, 0xA0, 0x6A, 0x7C };
    BitstreamReader br(std::move(data));

    auto aa = br.nextBits(16);
    auto a = br.nextBits(16);
    auto a2 = br.readBits(8);
    auto b = br.nextBits(16);
    auto b2 = br.readBits(8);

    EXPECT_EQ(a, aa);
    EXPECT_EQ(a, 0x2CA0);
    EXPECT_EQ(a2, 0x2C);
    EXPECT_EQ(b, 0xA06A);
    EXPECT_EQ(b2, 0xA0);
}

TEST(TestBitstreamReader, TestNextBitsUnalignedMultipleByte)
{
    std::vector<Byte> data{ 0x2C, 0xA0, 0x6A, 0x7C };
    BitstreamReader br(std::move(data));

    auto a = br.readBits(2);
    auto b = br.nextBits(3);
    auto b2 = br.readBits(5);
    auto b3 = br.readBits(9);

    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, 0x05);
    EXPECT_EQ(b2, 0x16);
    EXPECT_EQ(b3, 0xA0);

}

TEST(TestBitstreamReader, TestAdvancePos)
{
    std::vector<Byte> data{ 0x2C, 0xA0, 0x6A, 0x7C };
    BitstreamReader br(std::move(data));

    br.readBits(1);
    auto a = br.nextBits(3);
    br.advancePos(3);
    auto b = br.readBits(3);

    auto c = br.nextBits(3);
    br.advancePos(3);
    auto d = br.nextBits(3);

    EXPECT_NE(a, b);

    EXPECT_EQ(a, 2);
    EXPECT_EQ(b, 6);
    EXPECT_EQ(c, 2);
    EXPECT_EQ(d, 4);

}
