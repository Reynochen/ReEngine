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
    //Meshes
    Mesh testMesh(vertices, sizeof(vertices)/sizeof(Vertex), 0, 0);
    Mesh testMesh2(vertices, sizeof(vertices)/sizeof(Vertex), 0, 0);

    //Models
    std::vector<Model*> models;
    Model model(glm::vec3(0.f), &amogus, &amogus, "res/models/sphere.obj");

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


        model.render(&shader);
        // testTex.bind();
        // shader.setInt("Texture", testTex.getTexUnit());
        // testMesh.setPosition(glm::vec3(5.f, 0.f, 0.f));
        // testMesh.rotate(glm::vec3((float)glfwGetTime()*100, (float)glfwGetTime()*50, 0.f));
        // testMesh.render(&shader);

        // amogus.bind();
        // shader.setInt("Texture", amogus.getTexUnit());
        // testMesh2.rotate(glm::vec3(0.f, (float)glfwGetTime()*25, 0.f));
        // testMesh2.render(&shader);

        Window::swapBuffers();
        Events::pullEvents();
    }
}

Application* CreateApplication() {
    Application* app = new Application;
    return app;
}