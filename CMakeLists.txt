cmake_minimum_required(VERSION 3.18)

set(CMAKE_CUDA_FLAGS_INIT
    "--compiler-options=--sysroot=$ENV{SDKTARGETSYSROOT}"
)

set(CMAKE_EXE_LINKER_FLAGS_INIT
    "--sysroot=$ENV{SDKTARGETSYSROOT}"
)

set(CMAKE_CUDA_HOST_COMPILER $ENV{CXX})
set(CMAKE_CUDA_COMPILER "/usr/local/cuda-10.2/bin/nvcc")

project(MRP LANGUAGES CXX CUDA)

# ------------------------------------------------------------------------------
# Options
# ------------------------------------------------------------------------------
option(DBG "Enable debug build" OFF)

set(SM_ARCH 53 CACHE STRING "CUDA SM architecture (Jetson Nano = 53)")

# ------------------------------------------------------------------------------
# C++ / CUDA standards
# ------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CUDA_STANDARD 14)

if(DBG)
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -g -G")
else()
    set(CMAKE_BUILD_TYPE Release)
endif()

# ------------------------------------------------------------------------------
# GStreamer
# ------------------------------------------------------------------------------
find_package(PkgConfig REQUIRED)

pkg_check_modules(GST REQUIRED
    gstreamer-1.0
    gstreamer-app-1.0
)

pkg_check_modules(RTSP REQUIRED gstreamer-rtsp-server-1.0)

# ------------------------------------------------------------------------------
# Submodules
# ------------------------------------------------------------------------------
add_subdirectory(cudafunctions)

# ------------------------------------------------------------------------------
# Executable
# ------------------------------------------------------------------------------
add_executable(MRP
    main.cpp
)

# ------------------------------------------------------------------------------
# CUDA architecture
# ------------------------------------------------------------------------------
set_target_properties(MRP PROPERTIES
    CUDA_ARCHITECTURES ${SM_ARCH}
)

# ------------------------------------------------------------------------------
# Includes
# ------------------------------------------------------------------------------
target_include_directories(MRP PUBLIC
    /usr/include
    ${RTSP_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/datasource
    ${GST_INCLUDE_DIRS}
)

# ------------------------------------------------------------------------------
# Libraries
# ------------------------------------------------------------------------------

target_link_directories(MRP PRIVATE
    $ENV{SDKTARGETSYSROOT}/usr/lib
)

target_link_libraries(MRP PRIVATE
    cudafunctions
    ${GST_LIBRARIES}
    ${RTSP_LIBRARIES}
    nvbufsurface
    nvbuf_utils
    cudart
)

# ------------------------------------------------------------------------------
# Compiler flags from pkg-config
# ------------------------------------------------------------------------------
target_compile_options(MRP PRIVATE
    ${GST_CFLAGS_OTHER}
)