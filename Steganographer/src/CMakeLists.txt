cmake_minimum_required(VERSION 3.20)
project(StenographyApp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)

add_executable(StenographyApp
        StenographyApp.cpp
        Stenographer.cpp
)
