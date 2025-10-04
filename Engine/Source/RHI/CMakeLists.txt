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

# Compile all available RHIs
if (Vulkan_FOUND)
    target_sources(MapleRHI PRIVATE Private/RHI/Vulkan/VulkanRHI.cpp)
    target_link_libraries(MapleRHI PRIVATE Vulkan::Vulkan)
endif()

if (WIN32)
    # target_sources(MapleRHI PRIVATE Private/RHI/D3D12/D3D12RHI.cpp)
    target_link_libraries(MapleRHI PRIVATE d3d12 dxgi)
endif()

if (APPLE)
    # target_sources(MapleRHI PRIVATE Private/RHI/Metal/MetalRHI.cpp)
    target_link_libraries(MapleRHI PRIVATE "-framework Metal")
endif()

add_library(Maple::RHI ALIAS MapleRHI)
