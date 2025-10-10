# ======================================================================
# Renderer Dynamic Library
# ======================================================================
add_library(
    MapleRenderer SHARED
        Private/Renderer/RendererLog.cpp
        Private/Renderer/Renderer.cpp
)

target_compile_definitions(
    MapleRenderer
        # Private macros for internal implementation
        PRIVATE
            # For dynamic library import/export macros
            MAPLE_RENDERER_BUILD
)

target_include_directories(
    MapleRenderer
        # Public headers exposed to other modules
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public

        # Private headers for internal implementation
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(
    MapleRenderer
        # Private libraries for internal implementation
        PRIVATE
            Maple::Core
            Maple::Platform
            Maple::RHI
)

# Namespaced alias for consistent linking
add_library(Maple::Renderer ALIAS MapleRenderer)
