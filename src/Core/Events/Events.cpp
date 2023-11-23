#include "Events.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Window.hpp"
#include <math.h>

GLFWwindow* Events::window = nullptr;

bool Events::keys[1037];

bool Events::firstMouse = true;

float Events::deltaX,Events::deltaY;
float Events::lastX = 0.0f, Events::lastY = 0.0f;
float Events::lastFrame = 0.0f, Events::deltaTime = 0.0f;
unsigned int Events::inputCode = 0;
bool Events::pressAnything = false;

#include <iostream>

void Events::hideMouse(bool state) { /* Cursor switch function */
    if(window == nullptr) return;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (state*2));
}

void Events::pullEvents() {
    deltaX = 0.0f;
    deltaY = 0.0f;

    deltaTime = glfwGetTime() - lastFrame;
    lastFrame = glfwGetTime();

    pressAnything = false;
    glfwPollEvents();
}

void Events::initialization(GLFWwindow* window) {
    glfwSetKeyCallback(window, keyCallBack);
    glfwSetMouseButtonCallback(window, mouseButtonCallBack);
    glfwSetCursorPosCallback(window, cursorPosCallBack);
    glfwSetCharCallback(window, character_callback);

    Events::window = window;
    Events::hideMouse(true);
}

void Events::cursorPosCallBack(GLFWwindow* window, double xpos, double ypos) {
    if(!firstMouse) {
        deltaX += xpos - lastX;
        deltaY += lastY - ypos;
    }
    
    lastX = xpos;
    lastY = ypos;
    
    firstMouse = false;
}


void Events::mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods) {
    if(action == GLFW_PRESS)
        keys[button] = true;
    if(action == GLFW_RELEASE)
        keys[button] = false;
}
void Events::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS)
        keys[key] = true;
    if(action == GLFW_RELEASE)
        keys[key] = false;
}

bool Events::pressed(int key) {
    if(key <= 1024)
        return keys[key];
    return false;
}
bool Events::jpressed(int key) {
    if(key <= 1024) {
        bool lastKey = keys[key];
        keys[key] = false;
        return lastKey;
    }
    return false;
}

bool Events::clicked(int button) {
    if(button + 1025 <= 1037 && button + 1025 >= 1025)
        return keys[button];
    return false;
}
bool Events::jclicked(int button) {
    if(button + 1025 <= 1037 && button + 1025 >= 1025) {
        bool lastButton = keys[button];
        keys[button] = false;
        return lastButton;
    }
    return false;
}

void Events::character_callback(GLFWwindow* window, unsigned int codepoint) {
    inputCode = (unsigned int) codepoint;
    pressAnything = true;
}
unsigned int Events::getInputCode() {
    return inputCode;
}
bool Events::pressAnyKey() {
    return pressAnything;
}

float Events::getDeltaX() {return deltaX;}
float Events::getDeltaY() {return deltaY;}

float Events::getDeltaTime() { return deltaTime;}