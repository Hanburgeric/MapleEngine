# ======================================================================
# Dependencies
# ======================================================================
find_package(SDL3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

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

            # Enable designated initializers for Vulkan-Hpp
            VULKAN_HPP_NO_CONSTRUCTORS

            # Enable dynamic dispatcher for Vulkan extension functions
            VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1
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
            SDL3::SDL3
            Vulkan::Vulkan
            Maple::Core
            Maple::Platform
)

# ======================================================================
# Platform-Specific RHI Backend Compilation and Linking
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

# Namespaced alias for consistent linking
add_library(Maple::RHI ALIAS MapleRHI)
