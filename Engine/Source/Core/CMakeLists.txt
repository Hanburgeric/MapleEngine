# ======================================================================
# Dependencies
# ======================================================================
include(FetchContent)

FetchContent_Declare(
    EASTL
    GIT_REPOSITORY  https://github.com/electronicarts/EASTL.git
    GIT_TAG         3.27.00
)

FetchContent_Declare(
    glm
    GIT_REPOSITORY  https://github.com/g-truc/glm.git
    GIT_TAG         1.0.1
)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY  https://github.com/gabime/spdlog.git
    GIT_TAG         v1.15.3
)

FetchContent_MakeAvailable(
    EASTL glm spdlog
)

# ======================================================================
# Core Dynamic Library
# ======================================================================
add_library(
    MapleCore SHARED
        Private/Core/Log.cpp
)

target_compile_definitions(
    MapleCore
        # Public macros exposed to other modules
        PUBLIC
            # Define spdlog macros for compile-time log level filtering.
            # Logs below the active level are completely compiled out for
            # zero runtime overhead.
            $<$<CONFIG:Debug>:SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG>
            $<$<CONFIG:Release>:SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_INFO>

        # Private macros for internal implementation
        PRIVATE
            # For dynamic library import/export macros
            MAPLE_CORE_BUILD
)

target_include_directories(
    MapleCore
        # Public headers exposed to other modules
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public

        # Private headers for internal implementation
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(
    MapleCore
        # Public libraries exposed to other modules
        PUBLIC
            EASTL
            glm::glm
            spdlog::spdlog
)

# Namespaced alias for consistent linking
add_library(Maple::Core ALIAS MapleCore)
