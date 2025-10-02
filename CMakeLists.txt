cmake_minimum_required(VERSION 3.20)
project(MapleEngine LANGUAGES CXX)

# ======================================================================
# C++ Configuration
# ======================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ======================================================================
# Build Configuration
# ======================================================================
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ======================================================================
# Engine & Editor Subdirectories
# ======================================================================
add_subdirectory(Engine/Source)
add_subdirectory(Editor/Source)
