cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_COMPILER /usr/bin/gcc-8)
set(CMAKE_CXX_COMPILER /usr/bin/g++-8)

# THIS is the critical line
set(CMAKE_CUDA_HOST_COMPILER /usr/bin/g++-8)

project(cudafunctions LANGUAGES CXX CUDA)

# Collect sources
set(CPP_SOURCES
    benchmarkMemCopy.cpp
)

set(CUDA_SOURCES
    kernels/benchmarkMemCopy.cu
)

# Create library
add_library(cudafunctions
    ${CPP_SOURCES}
    ${CUDA_SOURCES}
)

# Include directories
target_include_directories(cudafunctions
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/kernels
)

# (Optional) set CUDA standard
set_target_properties(cudafunctions PROPERTIES
    CUDA_STANDARD 14
)