cmake_minimum_required(VERSION 3.22)

project(ReEngine)

add_executable(${PROJECT_NAME} main.cpp application/application.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Graphics
    glfw
    glad
)