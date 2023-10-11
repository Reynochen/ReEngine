#ifndef GLFW_WINDOW
#define GLFW_WINDOW

class GLFWwindow;

class Window {
    static GLFWwindow* _window;
    static int _width, _height;

public:
    static int initialization(int width, int height, const char* title);
    static int shouldClose();
    
    static void swapBuffers();
    static void terminate();
};

#endif