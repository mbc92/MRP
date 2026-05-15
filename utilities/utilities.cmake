# Utilities Library CMake Configuration

# Enable CUDA support
enable_language(CUDA)

# Set CUDA standard
set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CXX_STANDARD 14)

# Define CUDA SM architecture (Jetson Nano = 53)
set(SM_ARCH 53 CACHE STRING "CUDA SM architecture (Jetson Nano = 53)")

# ============================================================================
# Dependencies
# ============================================================================

# Include GStreamer configuration
include(${CMAKE_CURRENT_SOURCE_DIR}/utilities/gstreamer/gstreamer.cmake)

# ============================================================================
# Source Files
# ============================================================================

set(UTILITIES_SOURCES
    # CUDA Functions
    ${CMAKE_CURRENT_SOURCE_DIR}/utilities/cudafunctions/benchmark.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utilities/cudafunctions/kernels/benchmark.cu
    
    # GStreamer
    ${CMAKE_CURRENT_SOURCE_DIR}/utilities/gstreamer/gstreamer.cpp
)

# ============================================================================
# Create Shared Library
# ============================================================================

add_library(utilities SHARED ${UTILITIES_SOURCES})

# ============================================================================
# CUDA Configuration
# ============================================================================

set_target_properties(utilities PROPERTIES
    CUDA_ARCHITECTURES ${SM_ARCH}
    POSITION_INDEPENDENT_CODE ON
)

# ============================================================================
# Include Directories (PUBLIC)
# ============================================================================

target_include_directories(utilities PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/utilities/cudafunctions
    ${CMAKE_CURRENT_SOURCE_DIR}/utilities/cudafunctions/kernels
    ${CMAKE_CURRENT_SOURCE_DIR}/utilities/datasource
    ${CMAKE_CURRENT_SOURCE_DIR}/utilities/gstreamer
    ${GST_INCLUDE_DIRS}
    ${RTSP_INCLUDE_DIRS}
)

# ============================================================================
# Link Libraries
# ============================================================================

target_link_directories(utilities PUBLIC
    ${GST_LIBRARY_DIRS}
    ${RTSP_LIBRARY_DIRS}
)

target_link_libraries(utilities PUBLIC
    GStreamer::GStreamer
)

target_compile_options(utilities PRIVATE
    ${GSTREAMER_CFLAGS_OTHER}
    ${GSTREAMER_APP_CFLAGS_OTHER}
)

# Build type specific flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(utilities PRIVATE
        $<$<COMPILE_LANGUAGE:CUDA>:-g;-G>
    )
endif()

# ============================================================================
# Output Configuration
# ============================================================================

set_target_properties(utilities PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PREFIX "lib"
    SUFFIX ".so"
)

# ============================================================================
# Status Messages
# ============================================================================

message(STATUS "===== Utilities Library Configuration =====")
message(STATUS "Building utilities as SHARED library (.so)")
message(STATUS "CUDA Architecture: ${SM_ARCH}")
message(STATUS "GStreamer found: ${GSTREAMER_FOUND}")
message(STATUS "GStreamer version: ${GSTREAMER_VERSION}")
message(STATUS "GStreamer Video support: ${GSTREAMER_VIDEO_FOUND}")
message(STATUS "GStreamer Base support: ${GSTREAMER_BASE_FOUND}")
message(STATUS "Sources included:")
message(STATUS "  - CUDA Functions (benchmark)")
message(STATUS "  - GStreamer Integration")
message(STATUS "  - DataSource (header-only)")
message(STATUS "==========================================")
