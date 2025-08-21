cmake_minimum_required(VERSION 3.10)
project(JpegRegionCopy)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 源文件
set(SOURCES
    src/JpegCopier.cpp
    src/main.cpp
)

# 可执行文件
add_executable(jpeg_copy ${SOURCES})

# 包含目录
target_include_directories(jpeg_copy PRIVATE src)
