    cmake_minimum_required(VERSION 3.16.3)

project(TC2025_Proyecto2)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES
        ${CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

add_executable(${CMAKE_PROJECT_NAME}_Server src/server.c)
add_executable(${CMAKE_PROJECT_NAME}_Client src/client.c)

add_subdirectory(src)

find_package(OpenMP REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME}_Server Threads::Threads)
target_link_libraries(${CMAKE_PROJECT_NAME}_Server OpenMP::OpenMP_C)
target_link_libraries(${CMAKE_PROJECT_NAME}_Server m)
target_include_directories(${CMAKE_PROJECT_NAME}_Server PRIVATE lib)
target_compile_options(${CMAKE_PROJECT_NAME}_Server PRIVATE -O3 -Wall -Wextra -pedantic)

target_link_libraries(${CMAKE_PROJECT_NAME}_Client Threads::Threads)
target_link_libraries(${CMAKE_PROJECT_NAME}_Client m)