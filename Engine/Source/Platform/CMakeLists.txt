# ======================================================================
# Dependencies
# ======================================================================
find_package(Vulkan)

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL.git
    GIT_TAG         release-3.2.24
)

FetchContent_MakeAvailable(
    SDL3
)

# ======================================================================
# Platform Dynamic Library
# ======================================================================
add_library(
    MaplePlatform SHARED
        Private/Platform/PlatformLog.cpp
        Private/Platform/Window.cpp
)

target_compile_definitions(
    MaplePlatform
        # Private macros for internal implementation
        PRIVATE
            # For dynamic library import/export macros
            MAPLE_PLATFORM_BUILD
)

target_include_directories(
    MaplePlatform
        # Public headers exposed to other modules
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public

        # Private headers for internal implementation
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(
    MaplePlatform
        # Private libraries for internal implementation
        PRIVATE
            SDL3::SDL3
            Maple::Core
)

# ======================================================================
# Graphics API Detection
# ======================================================================
# D3D12 (Windows)
if (WIN32)
    target_compile_definitions(MaplePlatform PRIVATE MAPLE_D3D12_AVAILABLE)
    message(STATUS "MaplePlatform: D3D12 graphics API detected")
    set(PLATFORM_HAS_GRAPHICS_API TRUE)
endif()

# Metal (macOS & iOS)
if (APPLE)
    target_compile_definitions(MaplePlatform PRIVATE MAPLE_METAL_AVAILABLE)
    message(STATUS "MaplePlatform: Metal graphics API detected")
    set(PLATFORM_HAS_GRAPHICS_API TRUE)
endif()

# Vulkan (All Platforms)
if (Vulkan_FOUND)
    target_compile_definitions(MaplePlatform PRIVATE MAPLE_VULKAN_AVAILABLE)
    message(STATUS "MaplePlatform: Vulkan graphics API detected")
    set(PLATFORM_HAS_GRAPHICS_API TRUE)
endif()

# Ensure that at least one graphics API is available for use
if (NOT PLATFORM_HAS_GRAPHICS_API)
    message(FATAL_ERROR
            "MaplePlatform: No graphics API detected\n"
            "  - Build on Windows (D3D12 native)\n"
            "  - Build on macOS (Metal native)\n"
            "  - Or install the Vulkan SDK (All platforms)"
    )
endif()

# Namespaced alias for consistent linking
add_library(Maple::Platform ALIAS MaplePlatform)
