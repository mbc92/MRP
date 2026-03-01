cmake_minimum_required(VERSION 3.10)
project(MRP LANGUAGES CXX)

# Optional: set C++ standard globally
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optional: set binary output folder for all subprojects
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the base subdirectory (it has its own CMakeLists.txt)
add_subdirectory(base)

# You can add other subdirectories here in the future, e.g.,
# add_subdirectory(toolchains)
# add_subdirectory(utils)