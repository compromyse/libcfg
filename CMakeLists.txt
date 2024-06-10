cmake_minimum_required(VERSION 3.18)
project(libcfg)
set(CMAKE_C_FLAGS "-O3 -Wall -Wextra -Werror -pedantic")

add_library(cfg STATIC src/cfg.c)

add_executable(example examples/example.c)
target_link_libraries(example cfg)
configure_file(examples/example.cfg example.cfg COPYONLY)
