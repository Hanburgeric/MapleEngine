# ======================================================================
# Dependencies
# ======================================================================
find_package(Vulkan)

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL.git
    GIT_TAG         release-3.2.22
)

FetchContent_MakeAvailable(
    SDL3
)

# ======================================================================
# Application Dynamic Library
# ======================================================================
add_library(
    MapleApplication SHARED
        Private/Application/ApplicationLog.cpp
        Private/Application/Application.cpp
        Private/Application/Platform/WindowFactory.cpp
        Private/Application/Platform/SDL3/SDL3Window.cpp
)

target_compile_definitions(
    MapleApplication PRIVATE
        MAPLE_APPLICATION_BUILD
)

target_include_directories(
    MapleApplication
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(
    MapleApplication PRIVATE
        SDL3::SDL3
        Maple::Core
        Maple::RHI
)

# Vulkan (All Platforms)
if (Vulkan_FOUND)
    target_compile_definitions(MapleApplication PRIVATE MAPLE_VULKAN_AVAILABLE)
    message(STATUS "MapleApplication: Vulkan RHI detected")
    set(APPLICATION_HAS_RHI TRUE)
endif()

# D3D12 (Windows)
if (WIN32)
    target_compile_definitions(MapleApplication PRIVATE MAPLE_D3D12_AVAILABLE)
    message(STATUS "MapleApplication: D3D12 RHI detected")
    set(APPLICATION_HAS_RHI TRUE)
endif()

# Metal (MacOS & iOS)
if (APPLE)
    target_compile_definitions(MapleApplication PRIVATE MAPLE_METAL_AVAILABLE)
    message(STATUS "MapleApplication: Metal RHI detected")
    set(APPLICATION_HAS_RHI TRUE)
endif()

# Ensure that at least one RHI is available for use
if (NOT APPLICATION_HAS_RHI)
    message(FATAL_ERROR
            "MapleApplication: No RHI available\n"
            "  - Install the Vulkan SDK (All platforms)\n"
            "  - Or build on Windows (D3D12 native)\n"
            "  - Or build on MacOS (Metal native)"
    )
endif()

add_library(Maple::Application ALIAS MapleApplication)
