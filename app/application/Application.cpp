#include "Application.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Graphics.hpp"
#include "Camera.hpp"
#include "Events.hpp"
#include "Model.hpp"

#include <math.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OBJLoader.hpp"
#include "Object.hpp"

Application::Application() {
    Window::initialization(640, 480, "ReEngine", 0);
    Events::initialization(Window::getWindow());

    glClearColor(0.35, 0.77, 0.94, 0); //Sky color
    Window::swapBuffers();
    Window::swapBuffers();
}

Application::~Application() {
    Window::terminate();
}

void Application::run() {
    Model monkey(glm::vec3(5.f, 0.f, 0.f), "res/amogus.png", "res/amogus.png", "res/models/monke.obj");

    Object dominusObj(glm::vec3(0.f), new Model(glm::vec3(3.f, 0.f, -1.f), "res/white.jpg", "res/white.jpg", "res/models/dominus.obj"), "");

    Shader shader("res/shaders/mainShader/main.vs", "res/shaders/mainShader/main.fs"); //Create shader
    Camera camera(shader); //Create camera

    while (!Window::shouldClose())
    {
        camera.update();

        if (Events::pressed(GLFW_KEY_ESCAPE)) {
            Window::shouldClose(true);
        }

        shader.use();
        shader.setFloat("time", (float)glfwGetTime());
        shader.setVec3("viewPos", camera.Position);

        dominusObj.rotation = glm::vec3(0.f, (float)glfwGetTime()*glm::radians(50.f) ,0.f);
        monkey.rotation = glm::vec3(0.f, (float)glfwGetTime()*glm::radians(50.f) ,0.f);

        dominusObj.render(&shader);
        monkey.render(&shader);

        Window::swapBuffers();
        Events::pullEvents();
    }
}

Application* CreateApplication() {
    Application* app = new Application;
    return app;
}