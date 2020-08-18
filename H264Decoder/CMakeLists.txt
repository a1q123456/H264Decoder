cmake_minimum_required (VERSION 3.8)
project("LibH264Decoder")

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

# 将源代码添加到此项目的可执行文件。
add_library(LibH264Decoder STATIC  ${SRC_FILES})

set_target_properties(LibH264Decoder
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
target_precompile_headers(LibH264Decoder PRIVATE "pch.h")
target_include_directories(LibH264Decoder PUBLIC "${PROJECT_SOURCE_DIR}")




