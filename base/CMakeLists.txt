cmake_minimum_required(VERSION 3.10)
project(jetson_hello LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Put binaries in bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/datasource)

# Source files
set(SOURCES
    main.cpp
)

# Create executable
add_executable(main ${SOURCES})

# Optional compiler flags
# target_compile_options(main PRIVATE -Wall -Wextra -O3)