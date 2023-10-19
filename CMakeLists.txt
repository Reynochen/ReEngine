cmake_minimum_required(VERSION 3.22)

set( CMAKE_CXX_COMPILER "C:/mingw64/bin/g++.exe" )
set( CMAKE_C_COMPILER "C:/mingw64/bin/gcc.exe" )

project(ReEngine)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/../bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/../bin")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/glm)
add_subdirectory(external/stb_image)

add_subdirectory(src)
add_subdirectory(app)