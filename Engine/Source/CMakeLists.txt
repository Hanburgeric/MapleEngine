# ======================================================================
# Module Subdirectories
# ======================================================================
add_subdirectory(Application)
add_subdirectory(Core)
add_subdirectory(Platform)
add_subdirectory(RHI)

# ======================================================================
# Engine Interface Library
# ======================================================================
add_library(MapleEngine INTERFACE)

target_link_libraries(
    MapleEngine INTERFACE
        Maple::Application
        Maple::Core
        Maple::Platform
        Maple::RHI
)

# Namespaced alias for consistent linking
add_library(Maple::Engine ALIAS MapleEngine)
