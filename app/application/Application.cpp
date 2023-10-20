#include "Application.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Graphics.hpp"
#include "Camera.hpp"
#include "Events.hpp"

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

    Texture testTex("res/0o0.jpg", GL_TEXTURE_2D);
    //MODEL MESH
    Mesh test(vertices, sizeof(vertices)/sizeof(Vertex), 0, 0);

    Shader shader("res/shaders/mainShader/main.vs", "res/shaders/mainShader/main.fs"); //Create shader
    Camera camera(shader); //Create camera

    glm::mat4 model;

    glClearColor(0.35, 0.77, 0.94, 0); //Sky color
    while(!Window::shouldClose())
    {
        camera.update();

        if (Events::pressed(GLFW_KEY_ESCAPE)) {
            Window::shouldClose(true);
        }

        model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        shader.use();
        shader.setMat4("model", model);
        testTex.bind(0, GL_TEXTURE_2D);
        shader.setInt("Texture", 0);

        test.render(&shader);


        Window::swapBuffers();
        Events::pullEvents();
    }
}

void Application::updateDraw() {

}

Application* CreateApplication() {
    Application* app = new Application;
    return app;
}