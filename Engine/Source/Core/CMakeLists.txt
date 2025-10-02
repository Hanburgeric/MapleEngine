# ======================================================================
# Core Dynamic Library
# ======================================================================
add_library(
    MapleCore SHARED
        Private/Core/Engine.cpp
)

target_compile_definitions(
    MapleCore PRIVATE
        MAPLE_CORE_BUILD
)

target_include_directories(
    MapleCore
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

add_library(Maple::Core ALIAS MapleCore)
