# ======================================================================
# Dependencies
# ======================================================================
include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL.git
    GIT_TAG         release-3.2.22
)

FetchContent_MakeAvailable(
    SDL3
)

# ======================================================================
# Core Dynamic Library
# ======================================================================
add_library(
    MapleCore SHARED
        Private/Core/Application.cpp
        Private/Core/Platform/WindowFactory.cpp
        Private/Core/Platform/SDL3/SDL3Window.cpp
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

target_link_libraries(
    MapleCore PRIVATE
        SDL3::SDL3
)

add_library(Maple::Core ALIAS MapleCore)
