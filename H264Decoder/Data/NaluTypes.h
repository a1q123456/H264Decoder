#pragma once

enum class NaluTypes : std::uint8_t
{
    Unspecified = 0,
    CodedSliceNonIDRPicture,
    CodedSliceDataPartitionA,
    CodedSliceDataPartitionB,
    CodedSliceDataPartitionC,
    CodedSliceIDRPicture,
    SEI,
    SPS,
    PPS,
    AUD,
    EndOfSequence,
    EndOfStream,
    FilterData,
    SPSExtension,
    PrefixNALUnit,
    SubsetSPS,
    DPS,
    Reserved,
    PictureWithoutPartiting = 19,
    SliceLayerExtension,
    DepthOrThreeDAVCSliceLayerExtension,
    DepthOrTextureViewSliceLayerExtension,
    Reserved2,
    Unspecified2 = 24
};


