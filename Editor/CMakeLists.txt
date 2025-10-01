# ======================================================================
# Editor Executable
# ======================================================================
add_executable(
    MapleEditor
        Source/main.cpp
)

target_link_libraries(
    MapleEditor PRIVATE
        MapleEngine
)
