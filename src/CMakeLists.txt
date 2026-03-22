# ── Raylib ──────────────────────────────────────────────────────────────────
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        5.5
)
FetchContent_MakeAvailable(raylib)

# ── Main lib ────────────────────────────────────────────────────────────────
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(src_lib ${SOURCES})
target_include_directories(src_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(src_lib PRIVATE raylib)
