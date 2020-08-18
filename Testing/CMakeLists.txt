
cmake_minimum_required (VERSION 3.8)



add_executable(H264DecoderTesting  "TestBitstreamReader.cpp" "main.cpp")
target_precompile_headers(H264DecoderTesting PRIVATE "pch.h")
set_target_properties(H264DecoderTesting
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
target_precompile_headers(H264DecoderTesting PRIVATE "pch.h")
target_link_libraries(H264DecoderTesting PRIVATE LibH264Decoder)
target_include_directories(H264DecoderTesting PRIVATE "${PROJECT_SOURCE_DIR}")


find_package(GTest CONFIG REQUIRED)
target_link_libraries(H264DecoderTesting PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(H264DecoderTesting H264DecoderTesting)
