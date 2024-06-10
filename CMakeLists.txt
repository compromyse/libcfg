cmake_minimum_required(VERSION 3.18)
project(libcfg)
set(CMAKE_C_FLAGS "-O3 -Wall -Wextra")

add_library(cfg STATIC src/cfg.c)

add_executable(example examples/example.c)
target_link_libraries(example cfg)
