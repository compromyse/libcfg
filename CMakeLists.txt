cmake_minimum_required(VERSION 3.18)
project(libcfg)

add_library(libcfg STATIC src/cfg.c)

add_executable(example examples/example.c)
target_link_libraries(example libcfg)
