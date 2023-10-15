#ifndef GLFW_WINDOW
#define GLFW_WINDOW

class GLFWwindow;

class Window {
    static GLFWwindow* _window;
    static int _width, _height;

    static unsigned short _fpsLock;
    static double _lastTime;

    static void fpsLimit();
    static void winSizeCallBack(GLFWwindow* window, int width, int height);

public:
    static int initialization(int width, int height, const char* title, int fpsLock = 144);
    static int shouldClose();
    static void shouldClose(bool value);
    
    static void swapBuffers();
    static void terminate();

    static int getWidth();
    static int getHeight();

    static GLFWwindow* getWindow();
};

#endif