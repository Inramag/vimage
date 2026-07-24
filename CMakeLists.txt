cmake_minimum_required(VERSION 3.20)

project(vimage LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(vimage
    main.cpp
)

add_custom_command(TARGET vimage POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/raylib/lib/raylib.dll
        $<TARGET_FILE_DIR:vimage>
)

target_include_directories(vimage PRIVATE
    raylib/include
)

target_link_directories(vimage PRIVATE
    raylib/lib
)

target_link_libraries(vimage PRIVATE
    raylib
)