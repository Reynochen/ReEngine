#include "Window.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>

GLFWwindow* Window::_window;
int Window::_width, Window::_height;

int Window::initialization(int width, int height, const char* title) {
    if (!glfwInit()) {
        std::cout << "GLFW initialization failed.\n";
        return -1;
    }

    Window::_width = width;
    Window::_height = height;

    _window = glfwCreateWindow(_width, _height, title, nullptr, nullptr);

    if (!_window) {
        std::cout << "Window create failed.\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(_window);
    
    if(!gladLoadGL()) {
        std::cout << "GLAD initialization failed.\n";
        glfwTerminate();
        return -1;
    }

    return 0;
}

int Window::shouldClose() {
    return glfwWindowShouldClose(_window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(_window);
}

void Window::terminate() {
    glfwTerminate();
}