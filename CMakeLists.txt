cmake_minimum_required(VERSION 3.18)
project(libcfg)
if(NOT DEFINED CMAKE_C_FLAGS)
  set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic")
  set(CMAKE_C_FLAGS_DEBUG "-O0 -g")
  set(CMAKE_C_FLAGS_RELEASE "-O3 -Werror")
endif()

add_library(cfg STATIC src/cfg.c)

add_executable(example examples/example.c)
target_link_libraries(example cfg)
configure_file(examples/example.cfg example.cfg COPYONLY)
