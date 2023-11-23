#ifndef EVENTS
#define EVENTS

class GLFWwindow;

class Events {
    static GLFWwindow* window;

    static bool keys[1037];
    static float deltaTime;
    static float lastFrame;
    static bool pressAnything;
    static unsigned int inputCode;
    //Mouse
    static bool firstMouse;
    static float deltaX,deltaY, lastX,lastY;

    static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallBack(GLFWwindow* window, double xpos, double ypos);
    static void character_callback(GLFWwindow* window, unsigned int codepoint);

public:
    static unsigned int getInputCode();
    static bool pressAnyKey();

    static void initialization(GLFWwindow* window);
    static void pullEvents();

    static bool pressed(int key);
    static bool jpressed(int key);

    static bool clicked(int button);
    static bool jclicked(int button);

    static float getDeltaX(), getDeltaY();
    static float getDeltaTime();

    static void hideMouse(bool state);
    
    static void update();
};

#endif