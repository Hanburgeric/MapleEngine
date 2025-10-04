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
        PUBLIC
            # Define spdlog macros that allow compile-time log level filtering;
            # logs below the active level are compiled out for zero overhead.
            $<$<CONFIG:Debug>:SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG>
            $<$<CONFIG:Release>:SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_INFO>
        PRIVATE
            MAPLE_CORE_BUILD
)

target_include_directories(
    MapleCore
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(
    MapleCore PUBLIC
        EASTL
        glm::glm
        spdlog::spdlog
)

add_library(Maple::Core ALIAS MapleCore)
