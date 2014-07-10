# Project setup
project(mongo-sim)
cmake_minimum_required(VERSION 2.8.0)

add_definitions(-Wall)
add_definitions(-Werror)
add_definitions(-fPIC)
add_definitions(-std=c++11)
add_definitions(-g)
add_definitions(-O3)

enable_testing()

find_package(pkgconfig)
pkg_check_modules(LIBMONGOC    libmongoc-1.0)
pkg_check_modules(LIBBSON      libbson-1.0)

include_directories(${LIBMONGOC_INCLUDE_DIRS})
include_directories(${LIBBSON_INCLUDE_DIRS})

include_directories(src/codegen)
include_directories(src/simulation)
include_directories(src/simulation/bson)
include_directories(src/unittest)

add_subdirectory(src/codegen)
add_subdirectory(src/simulation)
add_subdirectory(src/unittest)
add_subdirectory(workloads)

