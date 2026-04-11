cmake_minimum_required(VERSION 3.10)
project(cudafunctions LANGUAGES CXX CUDA)

# ----------------------------
# Sources
# ----------------------------
set(CPP_SOURCES
    benchmark.cpp
)

set(CUDA_SOURCES
    kernels/benchmark.cu
)

add_library(cudafunctions
    ${CPP_SOURCES}
    ${CUDA_SOURCES}
)

# ----------------------------
# IMPORTANT: CUDA include path (SYSROOT)
# ----------------------------
set(JETSON_SYSROOT /opt/sdk-jetson-nano-xilinx/sysroots/armv8a-sorama-linux)

target_include_directories(cudafunctions
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/kernels
        ${JETSON_SYSROOT}/usr/local/cuda-10.2/include
        ${JETSON_SYSROOT}/usr/local/cuda-10.2/include/cuda
)

# IMPORTANT: link ONLY device runtime correctly
target_link_libraries(cudafunctions
    PRIVATE
        CUDA::cudart
)

# ----------------------------
# CUDA settings
# ----------------------------
set_target_properties(cudafunctions PROPERTIES
    CUDA_STANDARD 14
    CUDA_STANDARD_REQUIRED ON
)