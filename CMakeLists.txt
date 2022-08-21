cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(scala_compute_project)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
	yaml-cpp
	URL https://github.com/jbeder/yaml-cpp/archive/refs/tags/yaml-cpp-0.7.0.zip
)
set(yaml-cpp_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(yaml-cpp)

add_subdirectory(src)