#include "pch.h"
#include "RefPicListModification.h"
#include <Data\DecodingContext.h>

RefPicListModification::RefPicListModification(DecodingContext& context, BitstreamReader& reader)
{
    auto sliceType = 0;

    auto&& sliceHeader = context.currentSliceHeader();
    if (context.sliceHeaderIsSVC())
    {
        auto&& header = std::get<SliceHeaderInScalableExtension>(sliceHeader);
        sliceType = header.sliceType;
    }
    else if (context.sliceHeaderIs3DAVC())
    {
        auto&& header = std::get<SliceHeaderIn3DAVCExtension>(sliceHeader);
        sliceType = header.sliceType;
    }
    else if (context.hasSliceHeader())
    {
        auto&& header = std::get<SliceHeader>(sliceHeader);
        sliceType = header.sliceType;
    }
    else
    {
        throw std::runtime_error("no slice header");
    }

    if (sliceType % 5 != 2 && sliceType % 5 != 4)
    {
        refPicListModificationFlagl0 = reader.readBits<bool, 1>();
        if (refPicListModificationFlagl0)
        {
            while (refPicListModificationDatal0.emplace_back(reader).modificationOfPicNumIdc != 3)
            {

            }
        }
    }

    if (sliceType % 5 == 1)
    {
        refPicListModificationFlagl1 = reader.readBits<bool, 1>();
        if (refPicListModificationFlagl1)
        {
            while (refPicListModificationDatal1.emplace_back(reader).modificationOfPicNumIdc != 3)
            {

            }
        }
    }
}
