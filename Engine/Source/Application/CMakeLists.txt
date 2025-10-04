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
# Application Dynamic Library
# ======================================================================
add_library(
    MapleApplication SHARED
        Private/Application/ApplicationLog.cpp
        Private/Application/Application.cpp
        Private/Application/Platform/WindowFactory.cpp
        Private/Application/Platform/SDL3/SDL3Window.cpp
)

target_compile_definitions(
    MapleApplication PRIVATE
        MAPLE_APPLICATION_BUILD
)

target_include_directories(
    MapleApplication
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(
    MapleApplication PRIVATE
        SDL3::SDL3
        Maple::Core
)

add_library(Maple::Application ALIAS MapleApplication)
