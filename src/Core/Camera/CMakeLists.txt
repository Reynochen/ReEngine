file(GLOB cpp_file CONFIGURE_DEPENDS *.cpp)

project(Camera)

add_library(${PROJECT_NAME}
    ${cpp_file}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    "include"
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    glfw
    glad
)