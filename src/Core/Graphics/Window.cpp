#include "Window.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

GLFWwindow* Window::_window;
int Window::_width, Window::_height;

unsigned short Window::_fpsLock;
double Window::_lastTime = 0;

int Window::initialization(int width, int height, const char* title) {
    if (!glfwInit()) {
        std::cout << "GLFW initialization failed.\n";
        return -1;
    }

    Window::_width = width;
    Window::_height = height;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(_width, _height, title, nullptr, nullptr);

    if (!_window) {
        std::cout << "Window create failed.\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(_window);
    glfwSetWindowSizeCallback(_window, winSizeCallBack);
    
    if(!gladLoadGL()) {
        std::cout << "GLAD initialization failed.\n";
        glfwTerminate();
        return -1;
    }

    //Fix z view obj
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Hide inside polygones
    // glEnable(GL_CULL_FACE);
    // glFrontFace(GL_BACK);

    Window::_fpsLock = 60;

    return 0;
}

GLFWwindow* Window::getWindow() {
    return _window;
}

int Window::shouldClose() {
    return glfwWindowShouldClose(_window);
}
void Window::shouldClose(bool value) {
    glfwSetWindowShouldClose(_window, true);
}

void Window::swapBuffers() {
    glfwSwapBuffers(_window);
    fpsLimit();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::terminate() {
    glfwTerminate();
}

void Window::winSizeCallBack(GLFWwindow* window, int width, int height) {
    Window::_width = width;
    Window::_height = height;
    glViewport(0, 0, _width, _height);
}

void Window::fpsLimit() {
    //Vsync on crutches
    while(glfwGetTime() < _lastTime + 1.0/_fpsLock && _fpsLock != 0) {}
    _lastTime += 1.0/_fpsLock;
}

int Window::getWidth() {
    return _width;
}
int Window::getHeight() {
    return _height;
}