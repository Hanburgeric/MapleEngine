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
        Private/RHI/RHI.cpp
        Private/RHI/Vulkan/VulkanRHI.cpp
)

target_compile_definitions(
    MapleRHI
        # Private macros for internal implementation
        PRIVATE
            # For dynamic library import/export macros
            MAPLE_RHI_BUILD
)

target_include_directories(
    MapleRHI
        # Public headers exposed to other modules
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public

        # Private headers for internal implementation
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(
    MapleRHI
        # Private libraries for internal implementation
        PRIVATE
            Maple::Core
            Maple::Platform
)

# ======================================================================
# Backend Compilation and Linking
# ======================================================================
# D3D12 (Windows)
if (WIN32)
    # target_sources(MapleRHI PRIVATE Private/RHI/D3D12/D3D12RHI.cpp)
    target_link_libraries(MapleRHI PRIVATE d3d12 dxgi)
endif()

# Metal (macOS & iOS)
if (APPLE)
    # target_sources(MapleRHI PRIVATE Private/RHI/Metal/MetalRHI.cpp)
    target_link_libraries(MapleRHI PRIVATE "-framework Metal")
endif()

# Vulkan (All Platforms)
if (Vulkan_FOUND)
    target_sources(MapleRHI PRIVATE Private/RHI/Vulkan/VulkanRHI.cpp)
    target_link_libraries(MapleRHI PRIVATE Vulkan::Vulkan)
endif()

# Namespaced alias for consistent linking
add_library(Maple::RHI ALIAS MapleRHI)
