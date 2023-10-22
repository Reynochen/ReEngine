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

Application::Application() {
    Window::initialization(640, 480, "ReEngine", 0);
    Events::initialization(Window::getWindow());
}

Application::~Application() {
    Window::terminate();
}

void Application::run() {

    Vertex vertices[] = {
        glm::vec3(0.f, 0.5f, 0.f),          glm::vec3(1.f, 0.f, 0.f),   glm::vec2(0.f, 0.f),    glm::vec3(0.f, 0.f, 0.f),
        glm::vec3(-0.5f, -0.5f, 0.f),       glm::vec3(0.f, 1.f, 0.f),   glm::vec2(1.f, 0.f),    glm::vec3(0.f, 0.f, 0.f),
        glm::vec3(0.5f, -0.5f, 0.f),        glm::vec3(0.f, 0.f, 1.f),   glm::vec2(0.5f, 1.f),    glm::vec3(0.f, 0.f, 0.f),
    };

    Texture testTex("res/0o0.jpg", GL_TEXTURE_2D, 0);
    Texture amogus("res/amogus.png", GL_TEXTURE_2D, 0);

    //Models
    Model sphere(glm::vec3(0.f), &testTex, &testTex, "res/models/sphere.obj");
    Model monkey(glm::vec3(5.f, 0.f, 0.f), &amogus, &amogus, "res/models/monke.obj");

    Shader shader("res/shaders/mainShader/main.vs", "res/shaders/mainShader/main.fs"); //Create shader
    Camera camera(shader); //Create camera

    glClearColor(0.35, 0.77, 0.94, 0); //Sky color
    while(!Window::shouldClose())
    {
        camera.update();

        if (Events::pressed(GLFW_KEY_ESCAPE)) {
            Window::shouldClose(true);
        }

        shader.use();

        sphere.scale = glm::vec3(sin((float)glfwGetTime()));
        monkey.rotation = glm::vec3(0.f, (float)glfwGetTime()*glm::radians(50.f) ,0.f);

        sphere.render(&shader);
        monkey.render(&shader);

        Window::swapBuffers();
        Events::pullEvents();
    }
}

Application* CreateApplication() {
    Application* app = new Application;
    return app;
}