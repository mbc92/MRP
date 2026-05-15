cmake_minimum_required(VERSION 3.18)

# Only set project if this is the top-level build
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(utilities LANGUAGES CXX CUDA)
    
    # Set CUDA compiler for standalone build
    set(CMAKE_CUDA_COMPILER "/usr/local/cuda-10.2/bin/nvcc")
    
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CUDA_STANDARD 14)
    
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type")
endif()

# Include the utilities configuration
include(${CMAKE_CURRENT_SOURCE_DIR}/utilities.cmake)
