
cmake_minimum_required (VERSION 3.8)

add_executable(H264Decoder  "H264Decoder.cpp" "H264Decoder.h")
target_link_libraries(H264Decoder PRIVATE LibH264Decoder)
target_include_directories(H264Decoder PRIVATE "${PROJECT_SOURCE_DIR}")
target_precompile_headers(H264Decoder PRIVATE "pch.h")
set_target_properties(H264Decoder
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

