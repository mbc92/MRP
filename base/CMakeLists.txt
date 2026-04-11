cmake_minimum_required(VERSION 3.10)
project(jetson_hello LANGUAGES CXX CUDA)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
enable_language(CUDA)

# Put binaries in bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add cudafunctions subproject
add_subdirectory(cudafunctions)

# Source files
set(SOURCES
    main.cpp
)

# Create executable
add_executable(main ${SOURCES})

# Link your CUDA library
target_link_libraries(main PRIVATE cudafunctions)

# Modern include
target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/datasource
)

# Optional compiler flags
# target_compile_options(main PRIVATE -Wall -Wextra -O3)