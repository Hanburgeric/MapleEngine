# ======================================================================
# Editor Executable
# ======================================================================
add_executable(
    MapleEditor
        main.cpp
)

target_link_libraries(
    MapleEditor
        # Private libraries for internal implementation
        PRIVATE
            Maple::Engine
)
