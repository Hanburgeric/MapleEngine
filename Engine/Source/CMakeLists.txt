# ======================================================================
# Module Subdirectories
# ======================================================================
add_subdirectory(Core)

# ======================================================================
# Engine Interface Library
# ======================================================================
add_library(MapleEngine INTERFACE)

target_link_libraries(
    MapleEngine INTERFACE
        Maple::Core
)

add_library(Maple::Engine ALIAS MapleEngine)
