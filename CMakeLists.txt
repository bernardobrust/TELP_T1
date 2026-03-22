cmake_minimum_required(VERSION 3.20)

# CMAKE_HOST_SYSTEM_NAME (not CMAKE_SYSTEM_NAME) is available before project().
# On macOS, force GCC: Apple Clang's libc++ does not implement std::execution::par_unseq.
# Install GCC with: brew install gcc
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    set(GCC_CANDIDATE "")
    foreach(ver 15 14 13 12)
        find_program(GCC_NXX_${ver} NAMES g++-${ver}
            PATHS
                /opt/homebrew/bin
                /opt/homebrew/opt/gcc/bin
                /opt/homebrew/opt/gcc@15/bin
                /opt/homebrew/opt/gcc@14/bin
                /opt/homebrew/opt/gcc@13/bin
                /usr/local/bin
                /usr/local/opt/gcc/bin
            NO_DEFAULT_PATH)
        if(GCC_NXX_${ver})
            set(GCC_CANDIDATE "${GCC_NXX_${ver}}")
            break()
        endif()
    endforeach()
    if(NOT GCC_CANDIDATE)
        message(FATAL_ERROR
            "On macOS this project requires GCC (for std::execution::par_unseq).\n"
            "Install it with:  brew install gcc\n"
            "Then rebuild:     rm -rf build && mkdir build && cd build && cmake .. && make")
    endif()
    set(CMAKE_CXX_COMPILER "${GCC_CANDIDATE}" CACHE STRING "C++ compiler" FORCE)
    # Homebrew GCC needs the macOS SDK path to find system libraries (e.g. "System")
    execute_process(COMMAND xcrun --show-sdk-path OUTPUT_VARIABLE MACOS_SDK_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(CMAKE_OSX_SYSROOT "${MACOS_SDK_PATH}" CACHE PATH "macOS SDK" FORCE)
    message(STATUS "macOS detected: forcing GCC compiler -> ${GCC_CANDIDATE}")
endif()

project(TELP_T1 VERSION 1.0.0 LANGUAGES CXX)

# Guard: if somehow Apple Clang slipped through, fail loudly.
if(APPLE AND CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    message(FATAL_ERROR
        "Apple Clang does not support std::execution::par_unseq.\n"
        "Install GCC:  brew install gcc\n"
        "Then rebuild: rm -rf build && mkdir build && cd build && cmake .. && make")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(benchmarks)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE src_lib)