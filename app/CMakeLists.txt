cmake_minimum_required(VERSION 3.22)

project(ReEngine)

add_executable(${PROJECT_NAME} main.cpp application/application.cpp)

#Don't forget adding new module here ↓
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Graphics
    Object
    Camera
    Events
    glfw
    glad
    glm
)

# target_link_options(${PROJECT_NAME} PRIVATE -mwindows) #Off console