file(GLOB cpp_file CONFIGURE_DEPENDS *.cpp)

project(Object)

add_library(${PROJECT_NAME}
    ${cpp_file}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    "include"
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Graphics
    Camera
    Events
    glfw
    glad
    glm
)