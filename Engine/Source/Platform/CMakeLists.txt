# ======================================================================
# Dependencies
# ======================================================================
find_package(SDL3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

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
            Vulkan::Vulkan
            Maple::Core
)

# ======================================================================
# Platform-Specific Graphics API Detection
# ======================================================================
# D3D12 (Windows)
if (WIN32)
    target_compile_definitions(MaplePlatform PRIVATE MAPLE_D3D12_AVAILABLE)
    message(STATUS "MaplePlatform: D3D12 graphics API detected")
endif()

# Metal (macOS & iOS)
if (APPLE)
    target_compile_definitions(MaplePlatform PRIVATE MAPLE_METAL_AVAILABLE)
    message(STATUS "MaplePlatform: Metal graphics API detected")
endif()

# Namespaced alias for consistent linking
add_library(Maple::Platform ALIAS MaplePlatform)
