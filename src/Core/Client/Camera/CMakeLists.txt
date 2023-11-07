project(Camera)

file(GLOB cpp_file CONFIGURE_DEPENDS *.cpp)

add_library(${PROJECT_NAME}   
    ${cpp_file}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    glfw
    glad
    glm
    Events
    Graphics
)