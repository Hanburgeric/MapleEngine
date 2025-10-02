# ======================================================================
# Editor Executable
# ======================================================================
add_executable(
    MapleEditor
        main.cpp
)

target_link_libraries(
    MapleEditor PRIVATE
        Maple::Engine
)
