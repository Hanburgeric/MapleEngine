cmake_minimum_required(VERSION 3.25)
project(MapleEngine LANGUAGES CXX)

# Allow legacy dependencies with old CMake requirements (e.g., EASTL)
set(CMAKE_POLICY_VERSION_MINIMUM 3.25)

# ======================================================================
# C++ Configuration
# ======================================================================
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Hide symbols by default in dynamic libraries
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

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
