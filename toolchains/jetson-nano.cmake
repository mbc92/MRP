# Target system
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Use extracted sysroot
set(CMAKE_SYSROOT /opt/sdk-jetson-nano-xilinx/sysroots/armv8a-sorama-linux)

# Cross compiler
set(CMAKE_C_COMPILER /usr/bin/aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++)

# Find libraries in sysroot
set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# CUDA setup for JetPack 4.6 / CUDA 10.2
set(CUDA_TOOLKIT_ROOT_DIR /usr/local/cuda-10.2)
set(CMAKE_CUDA_COMPILER ${CUDA_TOOLKIT_ROOT_DIR}/bin/nvcc)
set(CMAKE_CUDA_FLAGS "--generate-code arch=compute_53,code=sm_53")

set(CMAKE_EXE_LINKER_FLAGS "--sysroot=${CMAKE_SYSROOT}")