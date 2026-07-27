cmake_minimum_required(VERSION 3.20)

project(vimage LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(vimage WIN32
    src/main.cpp

    src/app.cpp
    src/error.cpp
    src/stb/stb_image.cpp
    src/vimage.cpp
    src/viewer.cpp

    icon.rc
)

target_compile_options(vimage PRIVATE
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Release>:-DNDEBUG>

    -Wall
    -Wextra
    -Wpedantic
)

target_link_options(vimage PRIVATE
    $<$<CONFIG:Release>:-s>
    -static-libgcc
    -static-libstdc++
)

include(CheckIPOSupported)

check_ipo_supported(RESULT IPO_SUPPORTED)

if(IPO_SUPPORTED)
    set_property(TARGET vimage PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
endif()

target_include_directories(vimage PRIVATE
    include
    raylib/include
)

target_link_directories(vimage PRIVATE
    raylib/lib
)

target_link_libraries(vimage PRIVATE
    ${CMAKE_SOURCE_DIR}/raylib/lib/libraylibdll.a
    winmm
)

add_custom_command(TARGET vimage POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/raylib/lib/raylib.dll
        $<TARGET_FILE_DIR:vimage>
)