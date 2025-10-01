# ======================================================================
# Engine DLL
# ======================================================================
add_library(
    MapleEngine SHARED
        Source/Engine.cpp Source/Engine.h
)

target_compile_definitions(
    MapleEngine PRIVATE
        ENGINE_BUILD
)

target_include_directories(
    MapleEngine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
)
