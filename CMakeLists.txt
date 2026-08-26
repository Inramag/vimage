cmake_minimum_required(VERSION 3.10)

project(vimage LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(vimage WIN32
    src/main.cpp

    src/error.cpp
    src/stb/stb_image.cpp
    src/vimage.cpp
    src/ui.cpp
    src/settings.cpp
    src/viewer.cpp

    src/unicode.cpp

    icon.rc
)

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

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(vimage PRIVATE -municode)
    target_link_options(vimage PRIVATE -municode)
endif()

add_custom_command(TARGET vimage POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/raylib/lib/raylib.dll
        $<TARGET_FILE_DIR:vimage>

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/README.md
        $<TARGET_FILE_DIR:vimage>

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:vimage>/assets
)
