# ======================================================================
# Application Dynamic Library
# ======================================================================
add_library(
    MapleApplication SHARED
        Private/Application/ApplicationLog.cpp
        Private/Application/Application.cpp
)

target_compile_definitions(
    MapleApplication
        # Private macros for internal implementation
        PRIVATE
            # For dynamic library import/export macros
            MAPLE_APPLICATION_BUILD
)

target_include_directories(
    MapleApplication
        # Public headers exposed to other modules
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public

        # Private headers for internal implementation
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(
    MapleApplication
        # Private libraries for internal implementation
        PRIVATE
            Maple::Core
            Maple::Platform
)

# Namespaced alias for consistent linking
add_library(Maple::Application ALIAS MapleApplication)
