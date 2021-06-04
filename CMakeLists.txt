cmake_minimum_required(VERSION 3.16.3)

project(TC2025-Proyecto2)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES
        ${CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

add_executable(${CMAKE_PROJECT_NAME} src/main.c)

add_subdirectory(src)

find_package(OpenMP REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} OpenMP::OpenMP_C)
target_link_libraries(${CMAKE_PROJECT_NAME} m)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -O3 -Wall -Wextra -pedantic)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE lib)