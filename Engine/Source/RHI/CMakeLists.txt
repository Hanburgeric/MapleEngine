# ======================================================================
# Dependencies
# ======================================================================
find_package(Vulkan)

# ======================================================================
# RHI Dynamic Library
# ======================================================================
add_library(
    MapleRHI SHARED
        Private/RHI/RHILog.cpp
)

target_compile_definitions(
    MapleRHI PRIVATE
        MAPLE_RHI_BUILD
)

target_include_directories(
    MapleRHI
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(
    MapleRHI PRIVATE
        Maple::Core
)

# Vulkan (All Platforms)
if (Vulkan_FOUND)
    target_sources(MapleRHI PRIVATE Private/RHI/Vulkan/VulkanRHI.cpp)
    target_compile_definitions(MapleRHI PUBLIC MAPLE_VULKAN_AVAILABLE)
    target_link_libraries(MapleRHI PRIVATE Vulkan::Vulkan)

    message(STATUS "MapleRHI: Vulkan backend detected")
    set(RHI_HAS_BACKEND TRUE)
endif()

# D3D12 (Windows)
if (WIN32)
    # TODO: implement and add D3D12 RHI source files
    target_compile_definitions(MapleRHI PUBLIC MAPLE_D3D12_AVAILABLE)
    target_link_libraries(MapleRHI PRIVATE d3d12 dxgi)

    message(STATUS "MapleRHI: D3D12 backend detected")
    set(RHI_HAS_BACKEND TRUE)
endif()

# Metal (MacOS & iOS)
if (APPLE)
    # TODO: implement and add Metal RHI source files
    target_compile_definitions(MapleRHI PUBLIC MAPLE_METAL_AVAILABLE)
    target_link_libraries(MapleRHI PRIVATE "-framework Metal")

    message(STATUS "MapleRHI: Metal backend detected")
    set(RHI_HAS_BACKEND TRUE)
endif()

# Ensure that at least one backend is available for use
if (NOT RHI_HAS_BACKEND)
    message(FATAL_ERROR
            "MapleRHI: No RHI backend available\n"
            "  - Install the Vulkan SDK (All platforms)\n"
            "  - Or build on Windows (D3D12 native)\n"
            "  - Or build on MacOS (Metal native)"
    )
endif()

add_library(Maple::RHI ALIAS MapleRHI)
