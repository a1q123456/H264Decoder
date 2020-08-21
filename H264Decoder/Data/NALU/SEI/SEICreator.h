#pragma once
#include <Data/NALUnit.h>
#include <Data/NALU/SEI/SEIType.h>

struct DecodingContext;

using SEICreatorMap = std::unordered_map<SEIType, std::function<std::shared_ptr<std::uint8_t>(DecodingContext&, BitstreamReader&, int, NALUnit&)>>;

const SEICreatorMap& getSEICreator();

