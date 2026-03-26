cmake_minimum_required(VERSION 3.10.0)
project(notcurses_game VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(NOTCURSES REQUIRED notcurses)

file(GLOB_RECURSE SOURCES
    "src/*.c"
    "lib/**/*.c"
    "include/**/*.c"
)

add_executable(notcurses_game ${SOURCES})

target_compile_options(notcurses_game PRIVATE
    -g -O1
    -Wall -Wextra -Wformat -Wshadow -Wconversion -Wsign-conversion -Wno-sign-conversion
    -fstack-protector-strong
    ${NOTCURSES_CFLAGS_OTHER}
)

target_include_directories(notcurses_game PRIVATE
    lib 
    include
    ${NOTCURSES_INCLUDE_DIRS}
)

target_link_libraries(notcurses_game 
    ${NOTCURSES_LIBRARIES}
)
